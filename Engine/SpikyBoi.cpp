#include "SpikyBoi.h"
#include "SpriteEffect.h"

SpikyBoi::SpikyBoi( const Vei2& pos )
	:
	pos( pos )
{}

void SpikyBoi::Update( float dt )
{
}

void SpikyBoi::Draw( Graphics& gfx ) const
{
	// gfx.DrawCircle( Vei2( pos ),radius,Colors::Red );

	gfx.DrawSprite( int( pos.x ) - radius,
		int( pos.y ) - radius,
		img,SpriteEffect::Chroma{ Colors::Magenta } );
}

Circle SpikyBoi::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}
