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
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;

	FrameTimer time;
	Player guy;
	std::vector<std::unique_ptr<Floor>> floors;
	std::vector<Crystal> crystals;
	std::vector<SpikyBoi> spikyBois;
	std::vector<Comet> comets;
	int curLevel = 0;

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
	static constexpr float titleFadeSpeed = 0.6f;

	CSurfPtr earthBG = SurfCodex::Fetch( "Images/BackgroundEarth.bmp" );
	// CSurfPtr moonBG = SurfCodex::Fetch( "Images/BackgroundMoon.bmp" );

	bool canSkip = false;
	bool canRestart = false;

	static constexpr int lunarStart = 15;
};