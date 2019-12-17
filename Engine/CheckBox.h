#pragma once

#include "Vec2.h"
#include <string>
#include "Graphics.h"
#include "Codex.h"

class CheckBox
{
public:
	CheckBox( const Vei2& center,const std::string& text );

	bool Update( const Vei2& mousePos,bool mouseDown );
	void Draw( Graphics& gfx ) const;

	void Read( const std::string& line );
	std::string Write() const;

	bool IsChecked() const;
private:
	Vei2 GetSize( const std::string& msg ) const;
	bool ContainsPoint( const Vei2& point ) const;
private:
	CFontPtr luckyPixel = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	CSurfPtr empty = SurfCodex::Fetch( "Images/CheckBoxEmpty.bmp" );
	CSurfPtr full = SurfCodex::Fetch( "Images/CheckBoxFull.bmp" );
	static constexpr Vei2 padding = { 16,16 };
	const Vei2 size;
	const Vei2 pos;
	const std::string text;
	bool hovering = false;
	bool canClick = false;
	bool checked = false;
};