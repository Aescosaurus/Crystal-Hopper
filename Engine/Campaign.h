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
	std::vector<Floor> floors;
	std::vector<Crystal> crystals;
	std::vector<SpikyBoi> spikyBois;
	int curLevel = 0;

	State gameState = State::Gameplay;
	EndLevelMenu endLevelScreen;
	Timer endLevelTimer = 1.5f;
	static constexpr int startPoints = 1200;
	int points = startPoints;
	Timer pointSubtracter = 1.0f;
	static constexpr int timePointVal = 1;
};