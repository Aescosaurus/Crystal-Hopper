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

#include "SpiffyBG.h"

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
	static constexpr float musicVol = 0.5f;
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
	// const CSurfPtr backgrounds[nPlanets] =
	// {
	// 	SurfCodex::Fetch( "Images/BackgroundEarth.bmp" ),
	// 	SurfCodex::Fetch( "Images/BackgroundMoon.bmp" ),
	// 	SurfCodex::Fetch( "Images/BackgroundMars.bmp" ),
	// 	SurfCodex::Fetch( "Images/BackgroundJupiter.bmp" ),
	// 	SurfCodex::Fetch( "Images/BackgroundJupiter.bmp" )
	// };
	SpiffyBG backgrounds[nPlanets] =
	{
		SpiffyBG{ {
			SpiffyBG::Layer{ Animation::Single( "Images/BGEarth1.bmp" ),Vec2::Zero(),Vec2::Zero(),Vec2::Zero() },
			SpiffyBG::Layer{ Animation{ 0,0,8 * 4,14 * 4,3,*SurfCodex::Fetch( "Images/BGEarth2.bmp" ),0.2f,true },Vec2{ 117.0f,76.0f },Vec2::Up() * 95.0f,Vec2::Up() * 500.0f },
			SpiffyBG::Layer{ Animation::Single( "Images/BGEarth3.bmp" ),Vec2{ 13.0f - 480.0f,61.0f },Vec2::Right() * 20.0f,Vec2{ 13.0f,0.0f } }
			} },
		SpiffyBG{ {
			SpiffyBG::Layer{ Animation::Single( "Images/BGMoon1.bmp" ),Vec2::Zero(),Vec2::Zero(),Vec2::Zero() },
			SpiffyBG::Layer{ Animation::Single( "Images/BGMoon2.bmp" ),Vec2::Zero(),Vec2::Left() * 15.0f,Vec2{ -480.0f,0.0f },0.35f }
			} },
		SpiffyBG{ {
			SpiffyBG::Layer{ Animation::Single( "Images/BGMars2.bmp" ),Vec2{ 0.0f,0.0f },Vec2::Up() * 3.0f,Vec2{ 0.0f,-534.0f } },
			SpiffyBG::Layer{ Animation::Single( "Images/BGMars1.bmp" ),Vec2{ 0.0f,50.0f },Vec2::Zero(),Vec2::Zero() }
			} },
		SpiffyBG{ {
			SpiffyBG::Layer{ Animation{ 0,0,240 * 4,117 * 4,5,*SurfCodex::Fetch( "Images/BGJupiter1.bmp" ),0.8f },Vec2::Zero(),Vec2::Zero(),Vec2::Zero() },
			SpiffyBG::Layer{ Animation::Single( "Images/BGJupiter2.bmp" ),Vec2{ 83.0f,151.0f },Vec2::Up() * 10.0f,Vec2::Up() * 200.0f },
			SpiffyBG::Layer{ Animation::Single( "Images/BGJupiter3.bmp" ),Vec2{ 0.0f,87.0f },Vec2::Zero(),Vec2::Zero() }
			} },
		SpiffyBG{ {
			SpiffyBG::Layer{ Animation::Single( "Images/BGJupiter1.bmp" ),Vec2::Zero(),Vec2::Zero(),Vec2::Zero() }
			} }
	};

	bool win = false;
	float slowdown = 0.0f;
	static constexpr float slowdownDuration = 0.001f;

	const CMusicPtr musics[nPlanets] =
	{
		MusicCodex::Fetch( "Audio/MusicEarth.wav" ),
		MusicCodex::Fetch( "Audio/MusicMoon.wav" ),
		MusicCodex::Fetch( "Audio/MusicMars.wav" ),
		MusicCodex::Fetch( "Audio/MusicJupiter.wav" ),
		MusicCodex::Fetch( "Audio/MusicJupiter.wav" )
	};
	int oldIndex = -1;

	CSoundPtr ouchSound = SoundCodex::Fetch( "Audio/PlayerOuch.wav" );
};