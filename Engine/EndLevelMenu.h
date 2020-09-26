#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Button.h"
#include "Mouse.h"
#include "Codex.h"
#include "Animation.h"

class EndLevelMenu
{
public:
	void Update( const Mouse& mouse,float dt );
	void Draw( Graphics& gfx ) const;

	void UpdatePoints( float percent,int points );
	void UpdateStarWeights( const std::vector<int>& weights );
	void Lose();
	void UnLose();
	void Reset();

	bool PressedRetry() const;
	bool PressedContinue() const;
	bool PressedMenu() const;
	int Points2Stars( float percent ) const;
	const int* GetStarWeights() const;
	bool HasLost() const;
private:
	const Vei2 size = Vei2( Vec2( Graphics::ScreenSize ) / 1.5f );
	const Vei2 pos = Graphics::GetCenter() - size / 2;
	Button retry = Button{ pos + size + Vei2{ -100,-70 },"Retry" };
	Button resume = Button{ pos + size + Vei2{ -330,-130 },"Continue" };
	Button menu = Button{ pos + size + Vei2{ -540,-70 },"Menu" };
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
	bool lost = false;

	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	CSurfPtr filledStar = SurfCodex::Fetch( "Images/FilledStar.bmp" );
	CSurfPtr emptyStar = SurfCodex::Fetch( "Images/EmptyStar.bmp" );

	CSurfPtr menuBGSpr = SurfCodex::Fetch( "Images/MenuBG.bmp" );
	Animation menuBGAnim = Animation{ 0,0,menuBGSpr->GetWidth(),menuBGSpr->GetHeight(),5,
		*SurfCodex::Fetch( "Images/MenuBGAnim.bmp" ),0.05f,false };
};