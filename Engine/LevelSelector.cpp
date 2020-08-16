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
	const auto mouseDown = mouse.LeftIsPressed();

	if( mouseDown )
	{
		const auto diff = mousePos - oldMousePos;
		starPos.x += diff.x;

		if( starPos.x < minStarPos ) starPos.x = minStarPos;
		if( starPos.x > maxStarPos ) starPos.x = maxStarPos;
	}

	menuButton.Update( mousePos,mouseDown );

	earth.Update( starPos,mousePos,mouseDown );
	moon.Update( starPos,mousePos,mouseDown );
	mars.Update( starPos,mousePos,mouseDown );
	jupiter.Update( starPos,mousePos,mouseDown );

	oldMousePos = mousePos;
}

void LevelSelector::Draw() const
{
	gfx.DrawSpriteNormal( starPos.x,starPos.y,
		*starsImg,SpriteEffect::Copy{} );

	menuButton.Draw( gfx );

	earth.Draw( starPos,gfx );
	moon.Draw( starPos,gfx );
	mars.Draw( starPos,gfx );
	jupiter.Draw( starPos,gfx );

	earth.DrawMenu( gfx );
	moon.DrawMenu( gfx );
	mars.DrawMenu( gfx );
	jupiter.DrawMenu( gfx );
}

void LevelSelector::Reset()
{
	oldMousePos = mouse.GetPos();
	starPos = Vei2{ 0,0 };
}

int LevelSelector::GotoLevel()
{
	int total = -1;
	total += earth.GetReaction();
	total += moon.GetReaction();
	total += mars.GetReaction();
	total += jupiter.GetReaction();
	return( total );
}

bool LevelSelector::BackToMenu() const
{
	return( menuButton.IsPressed() );
}
