#include "Comet.h"
#include "Rect.h"
#include "SpriteEffect.h"

Comet::Comet( const Vei2& pos,float dir )
	:
	pos( Vec2( pos ) ),
	rotate( 0,0,radius * 2,radius * 2,5,*surfSheet,0.2f )/*,
	rotMat( Matrix::Rotation( dir ) )*/
{
	auto tempVel = -Vec2::FromAngle( dir );

	const int screenEx = 50; // Random{ 10,300 };
	// This probably isn't the best way to do things but...
	while( OverlapsScreen( screenEx ) )
	{
		this->pos -= tempVel;
	}
	startPos = this->pos;
	this->pos -= tempVel;

	vel = tempVel * speed;
}

void Comet::Update( float dt )
{
	if( startMoving.IsDone() ) pos += vel * dt;
	else startMoving.Update( dt );

	if( !OverlapsScreen( 0 ) )
	{
		respawn.Update( dt );

		if( respawn.IsDone() )
		{
			pos = startPos + vel * dt;
			// respawn.ResetRng( Random{ -1.3f,-0.6f } );
			respawn.Reset();
		}
	}
	else respawn.Reset();

	rotate.Update( dt );

	if( spawnDust.Update( dt ) )
	{
		spawnDust.ResetRng( Random{ -0.1f,-0.4f } );
		CreateDust();
	}
}

void Comet::Draw( Graphics& gfx ) const
{
#if NDEBUG
	rotate.Draw( Vei2( pos ) - Vei2{ radius,radius },gfx,
		SpriteEffect::SafeChroma{ Colors::Magenta } );
#else
	if( Graphics::GetScreenRect().GetExpanded( -radius )
		.ContainsPoint( Vei2( pos ) ) )
	{
		gfx.DrawCircleSafe( Vei2( pos ),radius,Colors::Gray );
	}
#endif
}

void Comet::Destroy()
{
	pos = startPos;
}

void Comet::CreateDust()
{
	CreateDustAt( pos );
}

void Comet::CreateDustAt( const Vec2& loc )
{
	// particles->emplace_back( Explosion{ loc,
	// 	Explosion::Type::CometDust } );
}

Circle Comet::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

const Vec2& Comet::GetVel() const
{
	return( vel );
}

bool Comet::OverlapsScreen( int screenExpand ) const
{
	RectI hitbox = RectI{ Vei2( pos ) -
		Vei2{ radius,radius },radius * 2,radius * 2 };

	return( hitbox.IsOverlappingWith( Graphics
		::GetScreenRect().GetExpanded( screenExpand + 100 ) ) );
}
