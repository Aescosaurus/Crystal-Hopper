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

	pos += vel * dt;
	vel -= ( ( vel * ( 1.0f - velDecay ) ) * dt );

	// Hit test stuff.
	const auto hSize = Vec2( size ) / 2.0f;
	if( pos.x + hSize.x >= float( Graphics::ScreenWidth ) ||
		pos.x - hSize.x <= 0.0f )
	{
		pos.x -= vel.x * dt;
		vel.x *= -1.0f;
		vel *= bounceLoss;
	}
	if( pos.y + hSize.y >= float( Graphics::ScreenHeight ) ||
		pos.y - hSize.y <= 0.0f )
	{
		pos.y -= vel.y * dt;
		vel.y *= -1.0f;
		vel *= bounceLoss;
	}
}

void Player::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),8,Colors::Cyan );
}
