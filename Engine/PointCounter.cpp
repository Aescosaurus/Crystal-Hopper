#include "PointCounter.h"
#include "SpriteEffect.h"

PointCounter::PointCounter( int maxPoints )
	:
	area( 10,10 + width,10,10 + height ),
	maxPoints( maxPoints )
{}

void PointCounter::Update( int points,float dt )
{
	this->points = points;
	if( oldPoints > float( this->points ) )
	{
		oldPoints -= barMoveSpeed * dt;
	}
	if( oldPoints < float( points ) ) oldPoints = float( points );
}

void PointCounter::Draw( Graphics& gfx ) const
{
	gfx.DrawSpriteNormal( area.left - 4,area.top - 4,
		*barBorder,SpriteEffect::Chroma{ Colors::Magenta } );

	const auto barWidth = int( float( area.GetWidth() ) *
		( float( points ) / float( maxPoints ) ) );
	gfx.DrawRect( area.left,area.top,
		barWidth,area.GetHeight(),Colors::White );

	gfx.DrawRect( area.left + barWidth,area.top,
		int( float( area.GetWidth() ) * ( oldPoints / float( maxPoints ) ) ) - barWidth,
		area.GetHeight(),Colors::Red );
}
