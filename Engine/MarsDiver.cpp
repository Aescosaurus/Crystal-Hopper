#include "MarsDiver.h"
#include "SpriteEffect.h"
#include "ChiliUtils.h"

MarsDiver::MarsDiver( const Vec2& pos )
	:
	pos( pos )
{}

void MarsDiver::Update( const Vec2& playerPos,float dt )
{
	const Vec2 diffVec = playerPos -
		( pos - Vei2{ radius,radius } );
	const float distSq = diffVec.GetLengthSq<float>();

	retarget.Update( dt );

	if( /* distSq <= activationRange * activationRange && */
		retarget.IsDone() )
	{
		angle = diffVec.GetAngle<float>();

		if( distSq <= jumpRange * jumpRange )
		{
			retarget.Reset();

			target = playerPos;
			vel = ( target - pos ).GetNormalized() * speed;
		}
	}

	pos += vel * dt;
	vel -= ( ( vel * ( 1.0f - velDecay ) ) *
		( retarget.GetPercent() / 5.0f ) ) * dt;

	// Bounce off the edges of the screen.
	if( pos.x - float( radius ) < 1.0f ||
		pos.x + float( radius ) >
		float( Graphics::ScreenWidth - 1 ) )
	{
		vel.x *= -1.0f;
		pos += vel * dt;
	}
	if( pos.y - float( radius ) < 1.0f ||
		pos.y + float( radius ) >
		float( Graphics::ScreenHeight - 1 ) )
	{
		vel.y *= -1.0f;
		pos += vel * dt;
	}
}

void MarsDiver::Draw( Graphics& gfx ) const
{
#if NDEBUG
	gfx.DrawSprite( int( pos.x ) - radius,
		int( pos.y ) - radius,*pSurf,
		SpriteEffect::Chroma{ Colors::Magenta },
		Matrix::Rotation( angle + chili::pi / 2.0f ) );
#else
	gfx.DrawCircle( Vei2( pos ),radius,
		retarget.IsDone() ?
		Colors::Green : Colors::Red );
#endif
}

Circle MarsDiver::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

const Vec2& MarsDiver::GetVel() const
{
	return( vel );
}

