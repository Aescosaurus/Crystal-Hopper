#include "Comet.h"
#include "Rect.h"

Comet::Comet( const Vei2& pos,float dir )
	:
	pos( Vec2( pos ) )
{
	auto tempVel = -Vec2::FromAngle( dir );

	// This probably isn't the best way to do things but...
	while( OverlapsScreen() )
	{
		this->pos -= tempVel;
	}
	startPos = this->pos;

	vel = tempVel * speed;
}

void Comet::Update( float dt )
{
	pos += vel * dt;

	if( !OverlapsScreen() )
	{
		respawn.Update( dt );

		if( respawn.IsDone() )
		{
			pos = startPos + vel * dt;
			respawn.Reset();
		}
	}
	else respawn.Reset();
}

void Comet::Draw( Graphics& gfx ) const
{
	gfx.DrawCircleSafe( Vei2( pos ),radius,Colors::Red );
}

Circle Comet::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

const Vec2& Comet::GetVel() const
{
	return( vel );
}

bool Comet::OverlapsScreen() const
{
	RectI hitbox = RectI{ Vei2( pos ) -
		Vei2{ radius,radius },radius * 2,radius * 2 };
	return( hitbox.IsOverlappingWith( Graphics
		::GetScreenRect() ) );
}
