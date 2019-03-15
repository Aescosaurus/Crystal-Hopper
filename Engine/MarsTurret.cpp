#include "MarsTurret.h"
#include "SpriteEffect.h"

MarsTurret::MarsTurret( const Vec2& pos,float angle,
	std::vector<Bullet>& bullets )
	:
	pos( pos ),
	rotMat( Matrix::Rotation( angle ) ),
	baseAnim( 0,0,64,64,5,*pSurfSheet,0.2f ),
	topAnim( 0,64,64,64,5,*pSurfSheet,0.2f ),
	pBulletVec( &bullets ),
	angle( angle )
{}

void MarsTurret::Update( const Vec2& playerPos,float dt )
{
	// update timers and shoot bullets at player

	angle += ( 3.1415f / 24.0f ) * dt;
	rotMat = Matrix::Rotation( angle );
}

void MarsTurret::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );

	baseAnim.Draw( Vei2( pos ),gfx,
		SpriteEffect::Chroma{ Colors::Magenta },
		rotMat );

	topAnim.Draw( Vei2( pos ),gfx,
		SpriteEffect::Chroma{ Colors::Magenta },
		rotMat );
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
