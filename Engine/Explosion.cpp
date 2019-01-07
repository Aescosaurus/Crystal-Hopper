#include "Explosion.h"
#include "SpriteEffect.h"

Explosion::Explosion( const Vec2& pos )
	:
	pos( Vei2( pos ) ),
	fadeAway( 0,0,size.x,size.y,5,*surfSheet,0.2f )
{
}

void Explosion::Update( float dt )
{
	fadeAway.Update( dt );

	if( fadeAway.IsFinished() )
	{
		willDestroy = true;
	}
}

void Explosion::Draw( Graphics& gfx ) const
{
	if( !willDestroy )
	{
		fadeAway.Draw( pos - size / 2,gfx,
			SpriteEffect::Fade{ Colors::Magenta,
			1.0f - fadeAway.GetPercent() } );
	}
}

bool Explosion::Done() const
{
	return( willDestroy );
}
