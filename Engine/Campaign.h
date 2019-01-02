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

class Campaign
{
public:
	Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw();
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
	int curLevel = 0;
};