#include "GravityFlipper.h"
#include "SpriteEffect.h"

GravityFlipper::GravityFlipper( const Vec2& pos )
	:
	coll( pos,radius )
{}

void GravityFlipper::Draw( Graphics& gfx ) const
{
	gfx.DrawSpriteNormal( int( coll.pos.x - radius ),
		int( coll.pos.y - radius ),*img,
		SpriteEffect::Chroma{ Colors::Magenta } );
}

const Circle& GravityFlipper::GetColl() const
{
	return( coll );
}
