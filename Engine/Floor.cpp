#include "Floor.h"
#include "Matrix.h"
#include "SpriteEffect.h"
#include "Player.h"

Floor::Floor( const Vec2& pos,float angle )
	:
	Floor( pos,angle,SurfCodex::Fetch( "Images/Platform.bmp" ) )
{}

void Floor::Draw( Graphics& gfx ) const
{
#if !NDEBUG
	for( const auto& l : lines )
	{
		gfx.DrawLine( l.start,l.end,Colors::Gray );
	}
	
	for( const auto& c : corners )
	{
		gfx.DrawCircle( Vei2( c.pos ),int( c.radius ),
			Colors::Gray );
	}
#else
	// {
	// 	const auto drawPos = GetDrawPos();
	// 
	// 	gfx.DrawSprite( drawPos.x,drawPos.y,*img,
	// 		SpriteEffect::Chroma{ Colors::Magenta },
	// 		rotationMatrix );
	// }
	gfx.DrawSpriteNormal( int( drawPos.x ),int( drawPos.y ),
		rotatedImage,
		SpriteEffect::Chroma{ Colors::Magenta } );
#endif
}

bool Floor::HandleColl( Player& guy,float dt )
{
	float shortest = 9999.0f;
	const Line* collLine = nullptr;
	const Circle* collCirc = nullptr;

	// Check for a line to collide with.
	for( const auto& line : lines )
	{
		float tempDist = -1.0f;
		if( guy.CheckColl( line,tempDist ) )
		{
			if( tempDist < shortest )
			{
				shortest = tempDist;
				collLine = &line;
			}
		}
	}

	// Only check corners if we don't have a line to
	//  collide with.
	if( collLine == nullptr )
	{
		for( const auto& circ : corners )
		{
			float tempDist = -1.0f;
			if( guy.CheckColl( circ,tempDist ) )
			{
				if( tempDist < shortest )
				{
					shortest = tempDist;
					collCirc = &circ;
				}
			}
		}
	}

	bool collision = false;
	// Prefer to collide with a line over a corner.
	if( collLine != nullptr )
	{
		guy.CollideWith( *collLine,dt );
		collision = true;
	}
	else if( collCirc != nullptr )
	{
		guy.CollideWith( *collCirc,dt );
		collision = true;
	}

	return( collision );
}

const std::vector<Line>& Floor::GetLines() const
{
	return( lines );
}

const std::vector<Circle>& Floor::GetCorners() const
{
	return( corners );
}

Floor::Floor( const Vec2& pos,float angle,CSurfPtr img )
	:
	img( img ),
	center( pos ),
	rotationMatrix( Matrix::Rotation( angle ) ),
	rotatedImage( 0,0 )
{
	const auto& rotMat = rotationMatrix;

	const auto hSize = size / 2.3f;

	typedef const Vec2 CVec2;
	CVec2 ul = RotatePoint( pos - hSize,pos,rotMat );
	CVec2 ur = RotatePoint( pos + hSize.X() - hSize.Y(),
		pos,rotMat );
	CVec2 dl = RotatePoint( pos - hSize.X() + hSize.Y(),
		pos,rotMat );
	CVec2 dr = RotatePoint( pos + hSize,pos,rotMat );

	// Don't shift the order of these.
	lines.emplace_back( Line{ ul,ur } );
	lines.emplace_back( Line{ ur,dr } );
	lines.emplace_back( Line{ dr,dl } );
	lines.emplace_back( Line{ dl,ul } );

	// Shrink by 2 pixels so the corners can be detected.
	for( auto& l : lines ) l.ShrinkBy( 2.0f );

	corners.emplace_back( Circle{ ul,cornerSize } );
	corners.emplace_back( Circle{ ur,cornerSize } );
	corners.emplace_back( Circle{ dl,cornerSize } );
	corners.emplace_back( Circle{ dr,cornerSize } );

	const std::pair<Surface,Vei2> result = img->GetRotated( pos,angle );

	rotatedImage = result.first;
	drawPos = Vec2( result.second );
}

void Floor::MoveBy( const Vec2& amount )
{
	for( auto& line : lines )
	{
		line.start += amount;
		line.end += amount;
	}
	for( auto& corner : corners )
	{
		corner.pos += amount;
	}

	drawPos += amount;
}

Vei2 Floor::GetDrawPos() const
{
	return( Vei2{ int( center.x - size.x / 2.0f ),
		int( center.y - size.y / 2.0f ) } );
}

Vec2 Floor::RotatePoint( const Vec2& point,
	const Vec2& about,const Matrix& rotMat ) const
{
	Vec2 temp = point;

	temp -= about;
	temp = rotMat * temp;
	temp += about;

	return( temp );
}
