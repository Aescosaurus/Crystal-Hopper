#include "SpikyBoi.h"
#include "SpriteEffect.h"

SpikyBoi::SpikyBoi( const Vei2& pos )
	:
	pos( pos ),
	shake( 0,0,64,64,5,*surfSheet,0.2f )
{}

void SpikyBoi::Update( float dt )
{
	shake.Update( dt );
}

void SpikyBoi::Draw( Graphics& gfx ) const
{
	// gfx.DrawCircle( Vei2( pos ),radius,Colors::Red );

	// gfx.DrawSprite( int( pos.x ) - radius,
	// 	int( pos.y ) - radius,
	// 	img,SpriteEffect::Chroma{ Colors::Magenta } );
	shake.Draw( Vei2( pos ) - Vei2{ radius,radius },
		gfx,SpriteEffect::Chroma{ Colors::Magenta } );
}

Circle SpikyBoi::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}
