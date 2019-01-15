#include "Floor.h"
#include "Matrix.h"
#include "SpriteEffect.h"
#include "Player.h"

Floor::Floor( const Vec2& pos,float angle )
	:
	center( pos ),
	rotationMatrix( Matrix::Rotation( angle ) )
{
	const auto& rotMat = rotationMatrix;

	const auto hSize = size / 2.0f;

	Vec2 ul = RotatePoint( pos - hSize,pos,rotMat );
	Vec2 ur = RotatePoint( pos + hSize.X() - hSize.Y(),pos,rotMat );
	Vec2 dl = RotatePoint( pos - hSize.X() + hSize.Y(),pos,rotMat );
	Vec2 dr = RotatePoint( pos + hSize,pos,rotMat );

	// Don't shift the order of these.
	lines.emplace_back( Line{ ul,ur } );
	lines.emplace_back( Line{ ur,dr } );
	lines.emplace_back( Line{ dr,dl } );
	lines.emplace_back( Line{ dl,ul } );

	for( auto& l : lines ) l.ShrinkBy( 2.0f );

	corners.emplace_back( Circle{ ul,cornerSize } );
	corners.emplace_back( Circle{ ur,cornerSize } );
	corners.emplace_back( Circle{ dl,cornerSize } );
	corners.emplace_back( Circle{ dr,cornerSize } );
}

void Floor::Draw( Graphics& gfx ) const
{
	// for( const auto& l : lines )
	// {
	// 	gfx.DrawLine( l.start,l.end,Colors::Gray );
	// }
	// 
	// for( const auto& c : corners )
	// {
	// 	gfx.DrawCircle( Vei2( c.pos ),int( c.radius ),
	// 		Colors::Gray );
	// }

	gfx.DrawSprite( center.x - int( size.x / 2.0f ),
		center.y - int( size.y / 2.0f ),*img,
		SpriteEffect::Chroma{ Colors::Magenta },
		rotationMatrix );
}

void Floor::HandleColl( Player& guy,float dt )
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

	// Prefer to collide with a line over a corner.
	if( collLine != nullptr )
	{
		guy.CollideWith( *collLine,dt );
	}
	else if( collCirc != nullptr )
	{
		guy.CollideWith( *collCirc,dt );
	}
}

const std::vector<Line>& Floor::GetLines() const
{
	return( lines );
}

const std::vector<Circle>& Floor::GetCorners() const
{
	return( corners );
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
