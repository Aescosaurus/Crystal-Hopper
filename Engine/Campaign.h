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
#include "PointCounter.h"
#include "OptionsMenu.h"

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
#include "LevelEnder.h"

class Campaign
{
private:
	enum class State
	{
		Gameplay,
		EndLevel
	};
public:
	Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx,
		const OptionsMenu& optionsMenu );

	void Update();
	void Draw();

	void RestartLevel();
	void UpdateOptions();
	void LoadLevel( int levelToLoad );
	void StopMusic();

	bool BackToMenu();
	bool Win() const;
private:
	void GotoNextLevel();
	void OpenEndLevelScreen();
	// Adds floors and crystals and stuff.
	void ReadFile( const std::string& filename );
	void UpdateSaveInfo( bool initSave = false );
	// Call this with curLevel++ so I can keep const.
	std::string GetNextLevelName( int curLevel ) const;
	int Level2Index() const;
	void PlayerOuch( int damage );
public:
	static constexpr float musicVol = 0.05f;
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
	std::vector<LevelEnder> levelEnders;

	int curLevel = 0; // From 0.

	State gameState = State::Gameplay;
	EndLevelMenu endLevelScreen;
	Timer endLevelTimer = 1.5f;
	static constexpr int startPoints = 1200;
	int points = startPoints;
	Timer pointSubtracter = 1.0f;
	static constexpr int timePointVal = 1;
	PointCounter pointCounter; // What a genius name. D:<
	const OptionsMenu& optionsMenu;

	std::vector<std::unique_ptr<Explosion>> particles;

	std::string levelName = "";
	int jumpLimit = -1;
	int curJumps = 0;
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	float titlePercent = 1.0f;
	static constexpr float titleFadeSpeed = 0.41f;
	static constexpr float jumpSlowdown = 0.2f;

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

	bool win = false;
	float slowdown = 0.0f;
	static constexpr float slowdownDuration = 0.05f;

	const CMusicPtr musics[nPlanets] =
	{
		MusicCodex::Fetch( "Audio/MusicEarth.wav" ),
		MusicCodex::Fetch( "Audio/MusicMoon.wav" ),
		MusicCodex::Fetch( "Audio/MusicMars.wav" ),
		MusicCodex::Fetch( "Audio/MusicJupiter.wav" ),
		MusicCodex::Fetch( "Audio/MusicJupiter.wav" )
	};
	int oldIndex = -1;
};