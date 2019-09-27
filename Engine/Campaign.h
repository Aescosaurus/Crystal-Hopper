#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Player.h"
#include "FrameTimer.h"
#include "Line.h"
#include <vector>
#include "Floor.h"
#include "Crystal.h"
#include <string>
#include "EndLevelMenu.h"
#include "Timer.h"
#include "SpikyBoi.h"
#include "Codex.h"
#include <memory>
#include "MovingFloor.h"

#include "Comet.h"
#include "LunarFloor.h"
#include "LunarCrystal.h"
#include "FallingFloor.h"
#include "Stalagmite.h"

#include "MartianFloor.h"
#include "MartianCrystal.h"
#include "Marvin.h"
#include "MarsTurret.h"
#include "MarsDiver.h"

#include "JupiterFloor.h"
#include "JupiterCrystal.h"
#include "GravityFlipper.h"
#include "GravSlowField.h"
#include "GravRotator.h"

class Campaign
{
private:
	enum class State
	{
		Gameplay,
		EndLevel
	};
public:
	Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw();

	void RestartLevel();
private:
	void GotoNextLevel();
	// Adds floors and crystals and stuff.
	void ReadFile( const std::string& filename );
	// Call this with curLevel++ so I can keep const.
	std::string GetNextLevelName( int curLevel ) const;
	int Level2Index() const;
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;

	FrameTimer time;
	Player guy;

	std::vector<std::unique_ptr<Floor>> floors;
	std::vector<std::unique_ptr<Crystal>> crystals;
	std::vector<SpikyBoi> spikyBois;
	std::vector<Comet> comets;
	std::vector<Stalagmite> spikes;
	std::vector<Marvin> martians;
	std::vector<MarsTurret> marsTurrets;
	std::vector<MarsTurret::Bullet> marsTurretBullets;
	std::vector<MarsDiver> divers;
	std::vector<GravityFlipper> gravFlippers;
	std::vector<GravSlowField> gravSlows;
	std::vector<GravRotator> gravRotators;

	int curLevel = 56; // From 0.

	State gameState = State::Gameplay;
	EndLevelMenu endLevelScreen;
	Timer endLevelTimer = 1.5f;
	static constexpr int startPoints = 1200;
	int points = startPoints;
	Timer pointSubtracter = 1.0f;
	static constexpr int timePointVal = 1;

	std::vector<Explosion> particles;

	std::string levelName = "";
	int jumpLimit = -1;
	int curJumps = 0;
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	float titlePercent = 1.0f;
	static constexpr float titleFadeSpeed = 0.41f;

	// CSurfPtr earthBG = SurfCodex::Fetch( "Images/BackgroundEarth.bmp" );
	// CSurfPtr moonBG = SurfCodex::Fetch( "Images/BackgroundMoon.bmp" );

	bool canSkip = false;
	bool canRestart = false;

	static constexpr int lunarStart = 15;
	static constexpr int marsStart = 15 * 2;
	static constexpr int jupiterStart = 15 * 3;
	static constexpr int saturnStart = 15 * 4;

	static constexpr int nPlanets = 5;
	static constexpr float gravities[nPlanets] =
	{
		0.14f, // Earth
		0.07f, // Lunar
		0.09f, // Mars
		0.31f, // Jupiter
		0.18f  // Saturn
	};
	const CSurfPtr backgrounds[nPlanets] =
	{
		SurfCodex::Fetch( "Images/BackgroundEarth.bmp" ),
		SurfCodex::Fetch( "Images/BackgroundMoon.bmp" ),
		SurfCodex::Fetch( "Images/BackgroundMars.bmp" ),
		SurfCodex::Fetch( "Images/BackgroundJupiter.bmp" ),
		SurfCodex::Fetch( "Images/BackgroundJupiter.bmp" )
	};
};