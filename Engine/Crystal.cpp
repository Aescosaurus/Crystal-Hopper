#include "Crystal.h"
#include "SpriteEffect.h"
#include "Random.h"

Crystal::Crystal( const Vec2& pos )
	:
	Crystal( pos,SurfCodex::Fetch( "Images/CrystalAnim.bmp" ),
		Explosion::Type::CrystalDissolve )
{}

void Crystal::Update( float dt )
{
	sparkle.Update( dt );

	if( sparkle.IsFinished() )
	{
		sparkle.SetFrame( 0 );

		sparkleHold.Update( dt );
		if( sparkleHold.IsDone() )
		{
			sparkleHold.ResetRng( Random{ -2.5f,0.0f } );
			sparkle.Reset();
		}
	}
}

void Crystal::Draw( Graphics& gfx ) const
{
	if( !collected )
	{
		// gfx.DrawCircle( Vei2( pos ),radius,Colors::Cyan );
		sparkle.Draw( Vei2( pos ) - Vei2{ radius,radius },
			gfx,SpriteEffect::Chroma{ Colors::Magenta } );
	}
}

void Crystal::Collect()
{
	collected = true;
}

Circle Crystal::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

bool Crystal::WillRemove() const
{
	return( collected );
}

const Vec2& Crystal::GetPos() const
{
	return( pos );
}

Crystal::Crystal( const Vec2& pos,CSurfPtr surfSheet,Explosion::Type explType )
	:
	explType( explType ),
	pos( pos ),
	sparkle( 0,0,radius * 2,radius * 2,5,*surfSheet,0.2f )
{
	sparkleHold.ResetRng( Random{ -3.5f,-0.2f } );
	sparkle.Update( 99.0f );
}
