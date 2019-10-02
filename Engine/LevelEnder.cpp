#include "LevelEnder.h"
#include "SpriteEffect.h"
#include "Random.h"

LevelEnder::LevelEnder( const Vec2& pos,
	std::vector<std::unique_ptr<Explosion>>& particles )
	:
	coll( pos,float( radius ) ),
	spin( 0,0,32,32,5,*sprSheet,0.2f ),
	particles( &particles )
{}

void LevelEnder::Update( float dt )
{
	spin.Update( dt );

	if( int( Random{ 0,100 } ) < particleSpawnChance )
	{
		const Vec2 dir = Vec2{ float( Random{ -1.0f,1.0f } ),
			float( Random{ -1.0f,1.0f } ) }.GetNormalized();

		particles->emplace_back( std::make_unique<MovingExplosion>(
			coll.pos - dir * particleMoveSpeed *
			float( Random{ 1.0f,1.5f } ),
			Explosion::Type::DustDissipate,
			dir * particleMoveSpeed ) );
	}
}

void LevelEnder::Draw( Graphics& gfx ) const
{
#if NDEBUG
	const auto drawPos = Vei2( coll.pos -
		Vec2( Vei2{ radius,radius } ) );
	
	spin.Draw( drawPos,gfx,
		SpriteEffect::Chroma{ Colors::Magenta } );
#else
	gfx.DrawCircle( Vei2( coll.pos ),
		radius,Colors::Black );
#endif
}

const Circle& LevelEnder::GetColl() const
{
	return( coll );
}
