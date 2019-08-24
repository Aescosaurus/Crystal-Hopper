#include "Explosion.h"
#include "SpriteEffect.h"

CSurfPtr Explosion::surfSheets[int( Type::Count )] =
{
	SurfCodex::Fetch( "Images/ExplodeAnim.bmp" ),
	SurfCodex::Fetch( "Images/ConfettiAnim.bmp" ),
	SurfCodex::Fetch( "Images/CrystalDissolveAnim.bmp" ),
	SurfCodex::Fetch( "Images/MoonCrystalDissolveAnim.bmp" ),
	SurfCodex::Fetch( "Images/MarsCrystalDissolveAnim.bmp" ),
	SurfCodex::Fetch( "Images/JupiterCrystalDissolveAnim.bmp" ),
	SurfCodex::Fetch( "Images/CometDustAnim.bmp" ),
	SurfCodex::Fetch( "Images/GroundBounceAnim.bmp" ),
	SurfCodex::Fetch( "Images/MarsTurretBoopAnim.bmp" )
};

Explosion::Explosion( const Vec2& pos,Type t )
	:
	pos( Vei2( pos ) ),
	fadeAway( 0,0,size.x,size.y,5,
		*surfSheets[int( t )],0.2f )
{}

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
