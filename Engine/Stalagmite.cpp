#include "Stalagmite.h"
#include "SpriteEffect.h"

Stalagmite::Stalagmite( const Vec2& pos,float angle )
	:
	center( pos ),
	rotationMatrix( Matrix::Rotation( angle ) )
{
	const auto hSize = size / 2.0f;

	const Vec2 top = RotatePoint( pos - hSize.Y(),center,
		rotationMatrix );
	const Vec2 bl = RotatePoint( pos - hSize.X() + hSize.Y(),
		center,rotationMatrix );
	const Vec2 br = RotatePoint( pos + hSize.X() + hSize.Y(),
		center,rotationMatrix );

	lines.emplace_back( Line{ top,bl } );
	lines.emplace_back( Line{ bl,br } );
	lines.emplace_back( Line{ br,top } );

	corners.emplace_back( Circle{ top,cornerSize } );
	corners.emplace_back( Circle{ bl,cornerSize } );
	corners.emplace_back( Circle{ br,cornerSize } );
}

void Stalagmite::Draw( Graphics& gfx ) const
{
#if !NDEBUG
	for( const auto& line : lines )
	{
		gfx.DrawLineSafe( line.start,line.end,Colors::Red );
	}
	
	for( const auto& corner : corners )
	{
		gfx.DrawCircleSafe( Vei2( corner.pos ),
			int( corner.radius ),Colors::Red );
	}
#else
	gfx.DrawSprite( int( center.x - size.x / 2.0f ),
		int( center.y - size.y / 2.0f ),img->GetRect(),
		Graphics::GetScreenRect()
		.GetExpanded( Graphics::ScreenWidth ),*img,
		SpriteEffect::SafeChroma{ Colors::Magenta },
		rotationMatrix );
#endif
}

bool Stalagmite::HandleColl( Player& guy,float dt ) const
{
	for( const auto& corner : corners )
	{
		float tempDist = 0.0f;
		if( guy.CheckColl( corner,tempDist ) )
		{
			guy.CollideWith( corner,dt );
			return( true );
		}
	}

	// Collide with line only if no corner has been hit.
	for( const auto& line : lines )
	{
		float tempDist = 0.0f;
		if( guy.CheckColl( line,tempDist ) )
		{
			guy.CollideWith( line,dt );
			return( true );
		}
	}
	
	return( false );
}

Vec2 Stalagmite::RotatePoint( const Vec2& point,
	const Vec2& about,const Matrix& rotMat ) const
{
	Vec2 temp = point;

	temp -= about;
	temp = rotMat * temp;
	temp += about;

	return( temp );
}
