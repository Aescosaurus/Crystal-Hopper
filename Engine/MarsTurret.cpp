#include "MarsTurret.h"
#include "SpriteEffect.h"
#include "ChiliUtils.h"

MarsTurret::MarsTurret( const Vec2& pos,float angle,
	std::vector<Bullet>& bullets )
	:
	pos( pos ),
	rotMat( Matrix::Rotation( angle ) ),
	pBulletVec( &bullets ),
	turretAngle( angle ),
	rotatedImage( 0,0 )
{
	const auto result = pBaseSurf->GetRotated( pos,angle );

	rotatedImage = result.first;
	myDrawPos = result.second;
}

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

		shotSound->Play();
	}
}

void MarsTurret::Draw( Graphics& gfx ) const
{
	const auto drawPos = GetCenter();
#if NDEBUG
	gfx.DrawSpriteNormal( myDrawPos.x,myDrawPos.y,
		rotatedImage,SpriteEffect::Chroma{ Colors::Magenta } );

	gfx.DrawSprite( int( drawPos.x ),int( drawPos.y ),
		*pTopSurf,SpriteEffect::Chroma{ Colors::Magenta },
		Matrix::Rotation( turretAngle ) );
#else
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );
#endif
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

const Vec2& MarsTurret::GetPos() const
{
	return( pos );
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
#if NDEBUG
	const auto drawPos = Vei2( pos ) - Vei2{ radius,radius } * 2;

	gfx.DrawSprite( drawPos.x,drawPos.y,*pSurf,
		SpriteEffect::Chroma{ Colors::Magenta },
		Matrix::Rotation( rotAngle ) );
#else
	if( Graphics::GetScreenRect().GetExpanded( -radius )
		.ContainsPoint( Vei2( pos ) ) )
	{
		gfx.DrawCircle( Vei2( pos ),radius,Colors::Green );
	}
#endif
}

void MarsTurret::Bullet::Destroy()
{
	destroyed = true;
}

bool MarsTurret::Bullet::CheckColl( const std::vector<Line>& lines )
{
	float dist = 0.0f;
	for( const auto& l : lines )
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
		if( dist < float( radius ) ) return( true );
	}

	return( false );
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
