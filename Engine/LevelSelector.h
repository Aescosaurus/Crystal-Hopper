#pragma once

#include "Mouse.h"
#include "Graphics.h"
#include "Codex.h"
#include "PlanetMenu.h"

class LevelSelector
{
public:
	LevelSelector( const Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw() const;
private:
	const Mouse& mouse;
	Graphics& gfx;

	Vei2 oldMousePos = Vei2::Zero();
	CSurfPtr starsImg = SurfCodex::Fetch( "Images/BackgroundStars.bmp" );
	Vei2 starPos = Vei2{ 0,0 };
	int minStarPos;
	int maxStarPos = 0;

	PlanetMenu earth = PlanetMenu{ Vei2{ 300,350 },"Images/PlanetEarth.bmp" };
};