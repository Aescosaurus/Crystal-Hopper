#include "SpikyBoi.h"
#include "SpriteEffect.h"
#include "Random.h"

SpikyBoi::SpikyBoi( const Vei2& pos )
	:
	pos( pos ),
	shake( 0,0,64,64,5,*surfSheet,0.2f )
{
	shake.Update( Random{ 0.0f,1.0f } );
}

void SpikyBoi::Update( float dt )
{
	shake.Update( dt );
}

void SpikyBoi::Draw( Graphics& gfx ) const
{
#if NDEBUG
	shake.Draw( Vei2( pos ) - Vei2{ radius,radius },
		gfx,SpriteEffect::Chroma{ Colors::Magenta } );
#else
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Red );
#endif
}

Circle SpikyBoi::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}
