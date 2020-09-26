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

	for( int i = 0; i < 5; ++i )
	{
		if( float( points ) / float( maxPoints ) >= pointWeights[i] )
		{
			// gfx.DrawRect( area.left + int( float( area.GetWidth() ) * pointWeights[i] ),
			// 	area.top,
			// 	2,area.GetHeight(),
			// 	Colors::MakeRGB( 255,200,37 ) );
			gfx.DrawSpriteNormal( area.left + int( float( area.GetWidth() ) * pointWeights[i] ) - starSpr->GetWidth() / 2,
				area.top,*starSpr,SpriteEffect::Chroma{} );
		}
	}

	gfx.DrawRect( area.left + barWidth,area.top,
		int( float( area.GetWidth() ) * ( oldPoints / float( maxPoints ) ) ) - barWidth,
		area.GetHeight(),Colors::Red );
}

void PointCounter::UpdatePointWeights( const int* weights )
{
	for( int i = 0; i < 5; ++i )
	{
		pointWeights[i] = float( weights[i] ) / 100.0f;
	}
}
