#pragma once

#include "Vec2.h"
#include <string>
#include "Graphics.h"
#include "Font.h"
#include "Codex.h"

class Button
{
public:
	Button( const Vei2& center,const std::string& text );

	// Returns true if pressed.
	bool Update( const Vei2& mousePos,bool mouseDown );
	void Draw( Graphics& gfx ) const;
	void DrawBackground( Graphics& gfx ) const;

	void Reset();

	bool IsPressed() const;
	bool IsHovering() const;
private:
	Vei2 GetSize( const std::string& msg ) const;
	bool ContainsPoint( const Vei2& point ) const;
private:
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	static constexpr Vei2 padding = { 16,16 };
	const Vei2 size;
	const Vei2 pos;
	const std::string text;
	bool hovering = false;
	bool canClick = false;
	bool clicking = false;
	CSurfPtr edgeSpr = SurfCodex::Fetch( "Images/ButtonEdge.bmp" );
	CSurfPtr mainSpr = SurfCodex::Fetch( "Images/ButtonMid.bmp" );
	CSurfPtr edgeLit = SurfCodex::Fetch( "Images/ButtonEdgeLit.bmp" );
	CSurfPtr mainLit = SurfCodex::Fetch( "Images/ButtonMidLit.bmp" );
	Surface bg;
	Surface lit;
};