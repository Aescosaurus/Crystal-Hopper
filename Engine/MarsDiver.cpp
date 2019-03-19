#include "MarsDiver.h"

MarsDiver::MarsDiver( const Vec2& pos )
	:
	pos( pos )
{}

void MarsDiver::Update( const Vec2& playerPos,float dt )
{
	const Vec2 diffVec = playerPos - pos;

	retarget.Update( dt );

	if( diffVec.GetLengthSq<float>() <=
		activationRange * activationRange &&
		retarget.IsDone() )
	{
		angle = diffVec.GetAngle<float>();

		if( diffVec.GetLengthSq<float>() <=
			jumpRange * jumpRange )
		{
			retarget.Reset();

			target = playerPos;
			vel = ( target - pos ).GetNormalized() * speed;
		}
	}

	pos += vel * dt;
	vel -= ( ( vel * ( 1.0f - velDecay ) ) *
		( retarget.GetPercent() / 5.0f ) ) * dt;
}

void MarsDiver::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),radius,
		retarget.IsDone() ?
		Colors::Green : Colors::Red );
}

Circle MarsDiver::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}
