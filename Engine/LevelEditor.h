#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Codex.h"
#include "ChiliUtils.h"

class LevelEditor
{
public:
	LevelEditor( Keyboard& kbd,Mouse& mouse,Graphics& gfx );

	void Update();
	void Draw() const;
private:
	void WriteToFile();

	template<typename Effect>
	void DrawSpriteCentered( const Vei2& pos,const Surface& s,
		Effect eff,Matrix rotMat = Matrix::Rotation( 0.0f ) ) const
	{
		gfx.DrawSprite( pos.x - s.GetWidth() / 2,
			pos.y - s.GetHeight() / 2,s,eff,rotMat );
	}
private:
	Keyboard& kbd;
	Mouse& mouse;
	Graphics& gfx;
	static constexpr auto outFilePath = "Logs/LatestLevel.txt";

	CSurfPtr platformSpr = SurfCodex::Fetch( "Images/Platform.bmp" );

	std::vector<std::pair<Vei2,float>> platforms;

	bool canClick = false;
	static constexpr float rotationSpeed = chili::deg2rad( 5.0f );
	float curRotation = 0.0f;
};