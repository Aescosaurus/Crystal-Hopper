#pragma once

#include "Mouse.h"
#include "Graphics.h"
#include "Codex.h"
#include "PlanetMenu.h"
#include "Keyboard.h"

class LevelSelector
{
public:
	LevelSelector( const Mouse& mouse,const Keyboard& kbd,Graphics& gfx );

	void Update();
	void Draw() const;

	void Reset();
	
	// Tells what level to go to, -1 = no go.
	int GotoLevel();
	bool BackToMenu() const;
private:
	const Mouse& mouse;
	const Keyboard& kbd;
	Graphics& gfx;

	Vei2 oldMousePos = Vei2::Zero();
	CSurfPtr starsImg = SurfCodex::Fetch( "Images/BackgroundStars.bmp" );
	Vei2 starPos = Vei2{ 0,0 };
	int minStarPos = -680;
	int maxStarPos = 0;

	Button menuButton = Button{ Vei2{ 850,480 },"Menu" };

	PlanetMenu earth = PlanetMenu{ Vei2{ 300,350 },0,"Images/PlanetEarth" };
	PlanetMenu moon = PlanetMenu{ Vei2{ 440,230 },1,"Images/PlanetMoon" };
	PlanetMenu mars = PlanetMenu{ Vei2{ 840,270 },2,"Images/PlanetMars" };
	PlanetMenu jupiter = PlanetMenu{ Vei2{ 1210,210 },3,"Images/PlanetJupiter" };
};