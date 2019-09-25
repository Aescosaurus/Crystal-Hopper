#include "Marvin.h"
#include <cassert>
#include "SpriteEffect.h"

Marvin::Marvin( const Vei2& pos,float angle )
	:
	pos( Vec2( pos ) ),
	vel( Vec2::FromAngle( angle ) ),
	start( pos - vel * float( radius ) * 2.5f ),
	end( pos + vel * float( radius ) * 2.5f ),
	wobble( 0,0,64,64,5,*surfSheet,0.2f )
{
	assert( vel.x != 0.0f ); // Pretty important.
	vel *= speed;
}

void Marvin::Update( float dt )
{
	pos += vel * dt;

	if( pos.x < start.x || pos.x > end.x )
	{
		vel *= -1.0f;
		pos += vel * dt;
	}

	wobble.Update( dt );
}

void Marvin::Draw( Graphics& gfx ) const
{
#if NDEBUG
	wobble.Draw( Vei2( pos ) - Vei2{ radius,radius },
		gfx,SpriteEffect::Chroma{ Colors::Magenta } );
#else
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );
#endif
}

Circle Marvin::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

const Vec2& Marvin::GetVel() const
{
	return( vel );
}
