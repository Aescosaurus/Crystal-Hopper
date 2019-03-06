#include "Marvin.h"
#include <cassert>

Marvin::Marvin( const Vei2& pos,float angle )
	:
	pos( Vec2( pos ) ),
	vel( Vec2::FromAngle( angle ) ),
	start( pos - vel * float( radius ) * 2.5f ),
	end( pos + vel * float( radius ) * 2.5f )
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
}

void Marvin::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );
}

Circle Marvin::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

const Vec2& Marvin::GetVel() const
{
	return( vel );
}
