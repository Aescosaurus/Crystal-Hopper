#include "PlanetMenu.h"
#include "SpriteEffect.h"

PlanetMenu::PlanetMenu( const Vei2& pos,const std::string& img )
	:
	pos( pos ),
	img( SurfCodex::Fetch( img ) )
{
	( this->pos ).x -= ( this->img )->GetWidth() / 2;
	( this->pos ).y -= ( this->img )->GetHeight() / 2;
}

void PlanetMenu::Draw( const Vei2& offset,Graphics& gfx ) const
{
	// TODO: Rotating planets?
	gfx.DrawSpriteNormal( pos.x + offset.x,pos.y + offset.y,
		*img,SpriteEffect::Chroma{ Colors::Magenta } );
}
