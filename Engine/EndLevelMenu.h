#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Button.h"
#include "Mouse.h"

class EndLevelMenu
{
public:
	void Update( const Mouse& mouse );
	void Draw( Graphics& gfx ) const;

	void UpdatePoints( float percent,int points );
	void UpdateStarWeights( const std::vector<int>& weights );

	bool PressedRetry() const;
	bool PressedContinue() const;
private:
	int Points2Stars( float percent ) const;
private:
	const Vei2 size = Vei2( Vec2( Graphics::ScreenSize ) / 1.5f );
	const Vei2 pos = Graphics::GetCenter() - size / 2;
	Button retry = Button{ pos + size.Y() + Vei2{ 90,-70 },"Retry" };
	Button resume = Button{ pos + size + Vei2{ -130,-70 },"Continue" };
	static constexpr int scoreTiers = 5; // 5 stars!
	// These vary each level, defined in the file.
	int starBracketPercents[scoreTiers] =
	{
		1,
		25,
		50,
		75,
		95
	};
	int points;
	int stars;
};