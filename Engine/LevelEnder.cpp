#include "LevelEnder.h"
#include "SpriteEffect.h"

LevelEnder::LevelEnder( const Vec2& pos )
	:
	coll( pos,float( radius ) ),
	spin( 0,0,32,32,5,*sprSheet,0.2f )
{}

void LevelEnder::Update( float dt )
{
	spin.Update( dt );
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
