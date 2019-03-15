#include "MarsTurret.h"
#include "SpriteEffect.h"
#include "ChiliUtils.h"

MarsTurret::MarsTurret( const Vec2& pos,float angle,
	std::vector<Bullet>& bullets )
	:
	pos( pos ),
	rotMat( Matrix::Rotation( angle ) ),
	pBulletVec( &bullets ),
	turretAngle( angle )
{}

void MarsTurret::Update( const Vec2& playerPos,float dt )
{
	// update timers and shoot bullets at player

	turretAngle = ( playerPos - pos ).GetAngle<float>() +
		chili::pi / 2.0f;

	this->playerPos = playerPos;
}

void MarsTurret::Draw( Graphics& gfx ) const
{
	const auto drawPos = GetCenter();
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );

	gfx.DrawSprite( int( drawPos.x ),int( drawPos.y ),
		*pBaseSurf,SpriteEffect::Chroma{ Colors::Magenta },
		rotMat );

	gfx.DrawSprite( int( drawPos.x ),int( drawPos.y ),
		*pTopSurf,SpriteEffect::Chroma{ Colors::Magenta },
		Matrix::Rotation( turretAngle ) );

	gfx.DrawLine( pos,playerPos,Colors::Red );
}

void MarsTurret::Destroy()
{
	destroyed = true;
}

Circle MarsTurret::GetColl() const
{
	return( Circle{ pos,float( radius ) } );
}

bool MarsTurret::IsDestroyed() const
{
	return( destroyed );
}

Vec2 MarsTurret::GetCenter() const
{
	return( pos - Vec2{ float( radius ),float( radius ) } );
}

MarsTurret::Bullet::Bullet( const Vec2& start,
	const Vec2& target )
	:
	pos( start ),
	vel( ( target - start ).GetNormalized() * speed )
{}

void MarsTurret::Bullet::Update( float dt )
{
	// pos += vel * dt
}

void MarsTurret::Bullet::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );
}

void MarsTurret::Bullet::Destroy()
{
	destroyed = true;
}

Circle MarsTurret::Bullet::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

bool MarsTurret::Bullet::IsDestroyed() const
{
	return( destroyed );
}
