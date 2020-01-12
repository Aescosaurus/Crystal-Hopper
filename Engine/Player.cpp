#include "Player.h"
#include "SpriteEffect.h"
#include "ChiliUtils.h"

Player::Player( const Mouse& ms,std::vector<std::unique_ptr<Explosion>>& explosions,
	float grav )
	:
	pMouse( &ms ),
	mt( ms ),
	pos( Vec2( Graphics::GetCenter() ) ),
	vel( 0.0f,0.0f ),
	explosions( &explosions ),
	gravAcc( grav )
{}

void Player::Update( float dt )
{
	mt.Update( pos );

	hasJumped = false;

	if( canJump && mt.Released() && !jumpDisabled )
	{
		vel += mt.GetDiff() * speed * ( invertControls ? 1.0f : -1.0f );
		canJump = false;
		pointsLost += jumpPenalty;
		hasJumped = true;

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
			explosions->emplace_back( std::make_unique<Explosion>( pos,
				Explosion::Type::Explosion ) );
			if( curJumpExplosions > nExplosionsPerJump )
			{
				curJumpExplosions = 0;
				makingTrail = false;
			}
		}
	}

	vel += gravScale * gravAcc * slowPercent * dt * 60.0f;

	ClampSpeed();

	pos += vel * dt * 60.0f;
	vel -= ( ( vel * ( 1.0f - velDecay ) ) * dt * 60.0f );

	DontHitWalls( dt );

	if( vel.GetLengthSq<float>() > 0.2f )
	{
		rotMatrix = Matrix::Rotation( vel
			.GetAngle<float>() + chili::pi / 2.0f );
	}

	if( invincible )
	{
		if( invincibilityFrames.Update( dt ) )
		{
			invincibilityFrames.Reset();
			invincible = false;
		}
	}
}

void Player::Draw( Graphics& gfx ) const
{
	// All the particles from all objects are drawn here
	//  don't worry about it.
	for( int i = 0; i < int( explosions->size() ); ++i )
	{
		explosions->at( i )->Draw( gfx );
	}

	// gfx.DrawCircle( Vei2( pos ),size / 2,Colors::Orange );

	const auto safeChroma = SpriteEffect
		::SafeChroma{ Colors::Magenta };

	// Draw rotated player.  Flash when invincible.
	const int invulPerc = invincibilityFrames.GetPercent();
	if( !invincible || invulPerc % 4 == 0 )
	{
		gfx.DrawSprite( int( pos.x ) - size / 2 + 2,
			int( pos.y ) - size / 2,*pGuySpr,
			safeChroma,rotMatrix );
	}

	// Draw direction arrow.
	if( mt.GetMouse().LeftIsPressed() &&
		mt.DiffIsReal() )
	{
		gfx.DrawSprite( int( pos.x ) - pArrowSurf->GetWidth() / 2 + 2,
			int( pos.y ) - pArrowSurf->GetHeight() / 2,
			*pArrowSurf,safeChroma,Matrix::Rotation( ( mt
			.GetDiff() * ( invertControls ? 1.0f : -1.0f ) )
			.GetAngle<float>() ) );
	}

	// Draw mouse tracker.
	mt.Draw( canJump ? Colors::White : Colors::Red,gfx );
}

void Player::CollideWith( const Line& l,float dt )
{
	canJump = true;

	const auto perp = l.GetDiff().GetPerp().GetNormalized();
	vel = vel - ( perp * ( 2.0f * Vec2::Dot( vel,perp ) ) );

	ClampSpeed();
	pos += vel * dt * 60.0f;

	explosions->emplace_back( std::make_unique<Explosion>( pos,
		Explosion::Type::GroundBounce ) );
}

void Player::CollideWith( const Circle& c,float dt )
{
	canJump = true;

	vel *= -1.0f;

	ClampSpeed(); // Just in case.
	pos += vel * dt * 60.0f;

	explosions->emplace_back( std::make_unique<Explosion>( pos,
		Explosion::Type::GroundBounce ) );
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

void Player::Reset( std::vector<std::unique_ptr<Explosion>>& explosions,float grav )
{
	// pos = Vec2( Graphics::GetCenter() );
	// vel = { 0.0f,0.0f };
	*this = Player{ *pMouse,explosions,grav };
}

void Player::ResetLostPoints()
{
	pointsLost = 0;
}

void Player::DisableJumping()
{
	jumpDisabled = true;
}

void Player::AddVelocity( const Vec2& otherVel,float dt )
{
	vel += otherVel;
	ClampSpeed();
	pos += vel * dt;
	DontHitWalls( dt );
}

void Player::DontHitWalls( float dt )
{
	// Hit test on walls.
	const auto hSize = Vec2( Vei2{ size,size } ) / 2.0f;
	if( pos.x + hSize.x >= float( Graphics::ScreenWidth ) ||
		pos.x - hSize.x <= 0.0f )
	{
		canJump = true;
		pos.x -= vel.x * dt * 60.0f * 1.1f;
		vel.x *= -1.0f;
		vel *= bounceLoss;
		explosions->emplace_back( std::make_unique<Explosion>( pos,
			Explosion::Type::GroundBounce ) );
	}
	if( pos.y + hSize.y >= float( Graphics::ScreenHeight - 40 ) ||
		pos.y - hSize.y <= 0.0f )
	{
		canJump = true;
		pos.y -= vel.y * dt * 60.0f * 1.1f;
		vel.y *= -1.0f;
		vel *= bounceLoss;
		explosions->emplace_back( std::make_unique<Explosion>( pos,
			Explosion::Type::GroundBounce ) );
	}
}

void Player::ApplyInvul()
{
	if( !invincible )
	{
		invincible = true;
		invincibilityFrames.Reset();
	}
}

void Player::FlipGravity()
{
	gravScale *= -1.0f;
}

void Player::FlipSlowPercent()
{
	if( slowPercent == 0.2f ) slowPercent = 1.0f;
	else slowPercent = 0.2f;
}

void Player::RotateGravity()
{
	std::swap( gravScale.x,gravScale.y );
	gravScale.x *= -1.0f;
}

void Player::SetInvertControls( bool invert )
{
	invertControls = invert;
}

void Player::SetClickMovement( bool click )
{
	mt.SetClickMovement( click );
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

bool Player::HasJumped() const
{
	return( hasJumped );
}

bool Player::IsInvincible() const
{
	return( invincible );
}

Vec2 Player::GetCurGravity() const
{
	return( gravScale * gravAcc * slowPercent );
}
