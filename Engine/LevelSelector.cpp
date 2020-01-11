#include "LevelSelector.h"
#include "SpriteEffect.h"

LevelSelector::LevelSelector( const Mouse& mouse,Graphics& gfx )
	:
	mouse( mouse ),
	gfx( gfx ),
	minStarPos( -starsImg->GetWidth() + Graphics::ScreenWidth )
{}

void LevelSelector::Update()
{
	// todo: dt stuff
	const auto mousePos = mouse.GetPos();

	if( mouse.LeftIsPressed() )
	{
		const auto diff = mousePos - oldMousePos;
		starPos.x += diff.x;

		if( starPos.x < minStarPos ) starPos.x = minStarPos;
		if( starPos.x > maxStarPos ) starPos.x = maxStarPos;
	}

	// earth.Update( mousePos );

	oldMousePos = mousePos;
}

void LevelSelector::Draw() const
{
	gfx.DrawSpriteNormal( starPos.x,starPos.y,
		*starsImg,SpriteEffect::Copy{} );

	earth.Draw( starPos,gfx );
}
