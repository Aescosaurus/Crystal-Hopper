#include "Floor.h"
#include "Matrix.h"

Floor::Floor( const Vec2& pos,const Vec2& size,float angle )
{
	lines.resize( 4 + 1 );

	const auto rotMat = Matrix::Rotation( angle );

	const auto hSize = size / 2.0f;
	// ul = rotMat * ( pos - hSize );
	// ur = rotMat * ( pos + hSize.X() - hSize.Y() );
	// dl = rotMat * ( pos - hSize.X() + hSize.Y() );
	// dr = rotMat * ( pos + hSize );
	ul = RotatePoint( pos - hSize,pos,rotMat );
	ur = RotatePoint( pos + hSize.X() - hSize.Y(),pos,rotMat );
	dl = RotatePoint( pos - hSize.X() + hSize.Y(),pos,rotMat );
	dr = RotatePoint( pos + hSize,pos,rotMat );

	GenerateLines();
}

void Floor::Draw( Graphics& gfx ) const
{
	for( const auto& l : lines )
	{
		gfx.DrawLine( l.start,l.end,Colors::Gray );
	}
}

void Floor::GenerateLines()
{
	lines.emplace_back( Line{ ul,ur } );
	lines.emplace_back( Line{ ur,dr } );
	lines.emplace_back( Line{ dr,dl } );
	lines.emplace_back( Line{ dl,ul } );
}

const std::vector<Line>& Floor::GetLines() const
{
	return( lines );
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
