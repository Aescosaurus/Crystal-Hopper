#include "Player.h"
#include "SpriteEffect.h"
#include "ChiliUtils.h"

Player::Player( const Mouse& ms )
	:
	pMouse( &ms ),
	mt( ms ),
	pos( Vec2( Graphics::GetCenter() ) ),
	vel( 0.0f,0.0f )
{}

void Player::Update( float dt )
{
	mt.Update();

	if( canJump && mt.Released() )
	{
		vel += mt.GetDiff() * speed;
		canJump = false;
		pointsLost += jumpPenalty;
		
		// explosionTrail.emplace_back( Explosion{ pos } );
		makingTrail = true;
	}

	if( makingTrail )
	{
		explSpawnTime.Update( dt );
		if( explSpawnTime.IsDone() )
		{
			explSpawnTime.Reset();
			++curJumpExplosions;
			explosionTrail.emplace_back( Explosion{ pos } );
			if( curJumpExplosions > nExplosionsPerJump )
			{
				curJumpExplosions = 0;
				makingTrail = false;
			}
		}
	}

	vel.y += gravAcc * dt * 60.0f;

	ClampSpeed();

	pos += vel * dt * 60.0f;
	vel -= ( ( vel * ( 1.0f - velDecay ) ) * dt * 60.0f );

	// Hit test stuff.
	const auto hSize = Vec2( Vei2{ size,size } ) / 2.0f;
	if( pos.x + hSize.x >= float( Graphics::ScreenWidth ) ||
		pos.x - hSize.x <= 0.0f )
	{
		canJump = true;
		pos.x -= vel.x * dt * 60.0f * 1.1f;
		vel.x *= -1.0f;
		vel *= bounceLoss;
	}
	if( pos.y + hSize.y >= float( Graphics::ScreenHeight ) ||
		pos.y - hSize.y <= 0.0f )
	{
		canJump = true;
		pos.y -= vel.y * dt * 60.0f * 1.1f;
		vel.y *= -1.0f;
		vel *= bounceLoss;
	}

	for( auto& expl : explosionTrail )
	{
		expl.Update( dt );
	}

	chili::remove_erase_if( explosionTrail,
		std::mem_fn( &Explosion::Done ) );
}

void Player::Draw( Graphics& gfx ) const
{
	for( const auto& expl : explosionTrail )
	{
		expl.Draw( gfx );
	}

	// gfx.DrawCircle( Vei2( pos ),size / 2,Colors::Orange );

	gfx.DrawSprite( int( pos.x ) - size / 2 + 2,
		int( pos.y ) - size / 2,*pGuySpr,
		SpriteEffect::SafeChroma{ Colors::Magenta },
		Matrix::Rotation( vel.GetAngle<float>() + chili::pi / 2.0f ) );

	mt.Draw( canJump ? Colors::White : Colors::Red,gfx );
}

void Player::CollideWith( const Line& l,float dt )
{
	canJump = true;

	const auto perp = l.GetDiff().GetPerp().GetNormalized();
	vel = vel - ( perp * ( 2.0f * Vec2::Dot( vel,perp ) ) );

	ClampSpeed();
	pos += vel * dt * 60.0f;
}

void Player::CollideWith( const Circle& c,float dt )
{
	canJump = true;

	vel *= -1.0f;

	ClampSpeed(); // Just in case.
	pos += vel * dt * 60.0f;
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

void Player::Reset()
{
	// pos = Vec2( Graphics::GetCenter() );
	// vel = { 0.0f,0.0f };
	*this = Player{ *pMouse };
}

void Player::ResetLostPoints()
{
	pointsLost = 0;
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

int Player::GetPointLoss() const
{
	return( pointsLost );
}
