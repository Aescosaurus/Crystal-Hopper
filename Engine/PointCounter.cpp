#include "PointCounter.h"

PointCounter::PointCounter( int maxPoints )
	:
	area( 10,10 + width,10,10 + height ),
	maxPoints( maxPoints )
{}

void PointCounter::Update( int points )
{
	this->points = points;
}

void PointCounter::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( area.left,area.top,
		float( area.GetWidth() ) * float( points ) / float( maxPoints ),
		area.GetHeight(),Colors::White );
}
