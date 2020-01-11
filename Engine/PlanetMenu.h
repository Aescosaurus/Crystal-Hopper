#pragma once

#include "Vec2.h"
#include <string>
#include "Graphics.h"
#include "Codex.h"
#include "Button.h"
#include <vector>

class PlanetMenu
{
public:
	PlanetMenu( const Vei2& pos,const std::string& img );

	void Update( const Vei2& offset,const Vei2& mousePos,bool mouseDown );
	void Draw( const Vei2& offset,Graphics& gfx ) const;

	// 1-15 0 = nothing
	int GetReaction() const;
private:
	Vei2 pos;
	CSurfPtr img;
	RectI clickArea;

	bool menuOpen = false;
	bool canClick = false;

	static constexpr Vei2 menuSize = Vei2( Vec2( Graphics::ScreenSize ) / 1.5 );
	static constexpr Vei2 menuPos = Graphics::ScreenCenter - menuSize / 2;
	std::vector<Button> levelButtons;
};