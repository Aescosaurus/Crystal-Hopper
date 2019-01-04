#pragma once

#include "Vec2.h"
#include <string>
#include "Graphics.h"
#include "Font.h"

class Button
{
public:
	Button( const Vei2& center,const std::string& text );

	// Returns true if pressed.
	bool Update( const Vei2& mousePos,bool mouseDown );
	void Draw( Graphics& gfx ) const;

	bool IsPressed() const;
private:
	Vei2 GetSize( const std::string& msg ) const;
	bool ContainsPoint( const Vei2& point ) const;
private:
	static const Font luckyPixel;
	static constexpr Vei2 padding = { 16,16 };
	const Vei2 size;
	const Vei2 pos;
	const std::string text;
	bool hovering = false;
	bool canClick = false;
	bool clicking = false;
};