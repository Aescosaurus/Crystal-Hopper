#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Codex.h"
#include "ChiliUtils.h"
#include "Button.h"

class LevelEditor
{
private:
	enum class Entity
	{
		Platform = 0,
		MoonPlatform,
		Crystal,
		MoonCrystal,
		SpikyBoi,
		MovingPlatform,
		Comet,
		FallingPlatform,
		Count
	};
public:
	LevelEditor( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw() const;

	void Reset();
private:
	void WriteToFile();

	template<typename Effect>
	void DrawSpriteCentered( const Vei2& pos,const Surface& s,
		Effect eff,Matrix rotMat = Matrix::Rotation( 0.0f ) ) const
	{
		gfx.DrawSprite( pos.x - s.GetWidth() / 2,
			pos.y - s.GetHeight() / 2,s,eff,rotMat );
	}

	void IncrementBrush();
	void DecrementBrush();
private:
	float ClampRotation( float rotation ) const;
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;
	static constexpr auto outFilePath = "Logs/LatestLevel.txt";

	std::vector<std::pair<Vei2,float>> entities[int( Entity::Count )] =
	{
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{},
		std::vector<std::pair<Vei2,float>>{}
	};

	bool canClick = false;
	static constexpr float rotationSpeed = chili::deg2rad( 5.0f );
	float curRotation = 0.0f;

	Entity brush = Entity::Platform;

	const Surface surfs[int( Entity::Count )] =
	{
		Surface{ "Images/Platform.bmp" },
		Surface{ "Images/MoonPlatform.bmp" },
		Surface{ Surface{ "Images/CrystalAnim.bmp" },RectI{ 0,48,0,48 } },
		Surface{ Surface{ "Images/MoonCrystalAnim.bmp" },RectI{ 0,48,0,48 } },
		Surface{ Surface{ "Images/SpikyBoiAnim.bmp" },RectI{ 0,64,0,64 } },
		Surface{ "Images/MovingPlatform.bmp" },
		Surface{ "Images/CometAnim.bmp" },
		Surface{ "Images/FallingPlatform.bmp" }
	};
	Button save = Button{ Vei2{ Graphics::ScreenWidth / 2,50 },"Save" };

	CSurfPtr earthBG = SurfCodex::Fetch( "Images/BackgroundEarth.bmp" );
	CSurfPtr moonBG = SurfCodex::Fetch( "Images/BackgroundMoon.bmp" );
};