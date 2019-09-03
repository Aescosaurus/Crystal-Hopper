#include "GravSlowField.h"
#include "SpriteEffect.h"

GravSlowField::GravSlowField( const Vec2& pos )
	:
	coll( pos,float( radius ) )
{}

void GravSlowField::Draw( Graphics& gfx ) const
{
	const auto drawPos = Vei2( coll.pos -
		Vec2( Vei2{ radius,radius } ) );

	gfx.DrawSpriteNormal( drawPos.x,drawPos.y,*img,
		SpriteEffect::Chroma{ Colors::Magenta } );
}

const Circle& GravSlowField::GetColl() const
{
	return( coll );
}
