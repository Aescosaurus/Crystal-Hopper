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
	turretAngle = ( playerPos - pos ).GetAngle<float>() +
		chili::pi / 2.0f;

	if( shotRefire.Update( dt ) )
	{
		shotRefire.Reset();

		pBulletVec->emplace_back( Bullet{ pos + Vec2
			::FromAngle( turretAngle - chili::pi / 2.0f ) *
			float( radius ),
			playerPos } );
	}
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
	vel( ( target - start ).GetNormalized() * speed ),
	rotAngle( ( target - start ).GetAngle<float>() )
{}

void MarsTurret::Bullet::Update( float dt )
{
	pos += vel * dt;

	rotAngle += rotSpeed * dt;


}

void MarsTurret::Bullet::Draw( Graphics& gfx ) const
{
	const auto drawPos = Vei2( pos ) - Vei2{ radius,radius } * 2;

	// gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );

	gfx.DrawSprite( drawPos.x,drawPos.y,*pSurf,
		SpriteEffect::Chroma{ Colors::Magenta },
		Matrix::Rotation( rotAngle ) );
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

const Vec2& MarsTurret::Bullet::GetPos() const
{
	return( pos );
}
