#include "Player.h"

Player::Player( MouseTracker& mt )
	:
	mt( mt ),
	pos( Vec2( Graphics::GetCenter() ) ),
	vel( 0.0f,0.0f )
{}

void Player::Update( float dt )
{
	if( mt.Released() ) vel += mt.GetDiff() * speed;

	vel.y += gravAcc * dt;

	ClampSpeed();

	pos += vel * dt;
	vel -= ( ( vel * ( 1.0f - velDecay ) ) * dt );

	// Hit test stuff.
	const auto hSize = Vec2( size,size ) / 2.0f;
	if( pos.x + hSize.x >= float( Graphics::ScreenWidth ) ||
		pos.x - hSize.x <= 0.0f )
	{
		pos.x -= vel.x * dt * 1.1f;
		vel.x *= -1.0f;
		vel *= bounceLoss;
	}
	if( pos.y + hSize.y >= float( Graphics::ScreenHeight ) ||
		pos.y - hSize.y <= 0.0f )
	{
		pos.y -= vel.y * dt * 1.1f;
		vel.y *= -1.0f;
		vel *= bounceLoss;
	}
}

void Player::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),size / 2,Colors::Orange );
}

void Player::CollideWith( const Line& l,float dt )
{
	const auto perp = l.GetDiff().GetPerp().GetNormalized();
	vel = vel - ( perp * ( 2.0f * Vec2::Dot( vel,perp ) ) );

	ClampSpeed();
	pos += vel * dt;
}

void Player::CollideWith( const Circle& c,float dt )
{
	vel *= -1.0f;

	ClampSpeed(); // Just in case.
	pos += vel * dt;
}

void Player::ClampSpeed()
{
	// vel.x = std::max( std::min( vel.x,50.0f ),-50.0f );
	// vel.y = std::max( std::min( vel.y,50.0f ),-50.0f );
	if( vel.GetLength<float>() > maxSpeed )
	{
		vel = vel.GetNormalized() * maxSpeed;
	}
}

void Player::ResetPos()
{
	pos.y = Vec2( Graphics::GetCenter() ).y;
}

bool Player::CheckColl( const Line& l,float& dist ) const
{
	const float lenSq = l.GetDiff().GetLengthSq<float>();
	if( lenSq == 0.0f )
	{
		dist = ( pos - l.start ).GetLength<float>();
	}
	else
	{
		const float t = std::max( 0.0f,std::min( 1.0f,Vec2
			::Dot( pos - l.start,l.GetDiff() ) / lenSq ) );
		const Vec2 proj = l.start + ( l.GetDiff() ) * t;
		dist = ( proj - pos ).GetLength<float>();
	}

	return( dist < size / 2 );
}

bool Player::CheckColl( const Circle& c,float& dist ) const
{
	dist = ( c.pos - pos ).GetLength<float>();

	return( dist < size / 2 + c.radius );
}

const Vec2& Player::GetPos() const
{
	return( pos );
}
