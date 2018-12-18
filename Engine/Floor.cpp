#include "Floor.h"
#include "Matrix.h"

Floor::Floor( const Vec2& pos,const Vec2& size,float angle )
{
	lines.resize( 4 + 1 );
	corners.resize( 4 + 1 );

	const auto rotMat = Matrix::Rotation( angle );

	const auto hSize = size / 2.0f;
	// ul = rotMat * ( pos - hSize );
	// ur = rotMat * ( pos + hSize.X() - hSize.Y() );
	// dl = rotMat * ( pos - hSize.X() + hSize.Y() );
	// dr = rotMat * ( pos + hSize );

	Vec2 ul = RotatePoint( pos - hSize,pos,rotMat );
	Vec2 ur = RotatePoint( pos + hSize.X() - hSize.Y(),pos,rotMat );
	Vec2 dl = RotatePoint( pos - hSize.X() + hSize.Y(),pos,rotMat );
	Vec2 dr = RotatePoint( pos + hSize,pos,rotMat );

	lines.emplace_back( Line{ ul,ur } );
	lines.emplace_back( Line{ ur,dr } );
	lines.emplace_back( Line{ dr,dl } );
	lines.emplace_back( Line{ dl,ul } );

	corners.emplace_back( Circle{ ul,cornerSize } );
	corners.emplace_back( Circle{ ur,cornerSize } );
	corners.emplace_back( Circle{ dl,cornerSize } );
	corners.emplace_back( Circle{ dr,cornerSize } );
}

void Floor::Draw( Graphics& gfx ) const
{
	for( const auto& l : lines )
	{
		gfx.DrawLine( l.start,l.end,Colors::Gray );
	}

	for( const auto& c : corners )
	{
		gfx.DrawCircle( Vei2( c.pos ),int( c.radius ),
			Colors::Gray );
	}
}

void Floor::MoveBy( const Vec2& moveAmount )
{
	for( auto& line : lines )
	{
		line.start += moveAmount;
		line.end += moveAmount;
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
