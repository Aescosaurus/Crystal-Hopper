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
	SurfCodex::Fetch( "Images/MarsTurretBoopAnim.bmp" ),
	SurfCodex::Fetch( "Images/ParticleDissipateAnim.bmp" )
};

Explosion::Explosion( const Vec2& pos,Type t,
	Behavior b )
	:
	pos( pos ),
	fadeAway( 0,0,size.x,size.y,5,
		*surfSheets[int( t )],0.2f ),
	behavior( b )
{}

void Explosion::Update( float dt )
{
	fadeAway.Update( dt );

	if( fadeAway.IsFinished() )
	{
		willDestroy = true;
	}
	
	switch( behavior )
	{
	case Behavior::Static:
		break;
	case Behavior::Falling:
		pos.y += fallSpeed * dt;
		break;
	}
}

void Explosion::Draw( Graphics& gfx ) const
{
#if NDEBUG
	if( !willDestroy )
	{
		fadeAway.Draw( pos - size / 2,gfx,
			SpriteEffect::Fade{ Colors::Magenta,
			1.0f - fadeAway.GetPercent() } );
	}
#else
	if( Graphics::GetScreenRect().GetExpanded( -size.x / 3 )
		.ContainsPoint( pos ) )
	{
		gfx.DrawCircle( pos,size.x / 3,Colors::Red );
	}
#endif
}

bool Explosion::Done() const
{
	return( willDestroy );
}
