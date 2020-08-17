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
	PlanetMenu( const Vei2& pos,int planetNum,const std::string& img );

	void Update( const Vei2& offset,const Vei2& mousePos,bool mouseDown );
	void Draw( const Vei2& offset,Graphics& gfx ) const;
	void DrawMenu( Graphics& gfx ) const;

	void ReloadSaveInfo();
	// 1-15 = level 0 = nothing
	int GetReaction();
private:
	Vei2 pos;
	int planetNum;
	CSurfPtr img;
	CSurfPtr grayImg;
	RectI clickArea;

	bool menuOpen = false;
	bool canClick = false;

	static constexpr Vei2 menuSize = Vei2( Vec2( Graphics::ScreenSize ) / 1.5 );
	static constexpr Vei2 menuPos = Graphics::ScreenCenter - menuSize / 2;
	std::vector<Button> levelButtons;
	std::vector<std::pair<Vei2,int>> levelStars;
	CSurfPtr filledStar = SurfCodex::Fetch( "Images/FilledPlanetStar.bmp" );
	CSurfPtr emptyStar = SurfCodex::Fetch( "Images/EmptyPlanetStar.bmp" );

	CSurfPtr lockIcon = SurfCodex::Fetch( "Images/Lock.bmp" );
};