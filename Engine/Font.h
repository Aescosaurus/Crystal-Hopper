#pragma once

#include "Surface.h"
#include "Vec2.h"
#include <string>
#include "Graphics.h"
#include "Rect.h"

class Font
{
public:
	Font( const std::string& fileName,Color chroma = Colors::White );

	void DrawText( const std::string& text,const Vei2& pos,Color color,Graphics& gfx ) const;
	template<typename Effect>
	void DrawText( const std::string& text,const Vei2& pos,
		Color col,Effect e,Graphics& gfx ) const
	{
		// SpriteEffect::Substitution e{ chroma,color };
		auto curPos = pos;
		for( auto c : text )
		{
			if( c == '\n' )
			{
				curPos.x = pos.x;
				curPos.y += glyphHeight;
				continue;
			}
			else if( c >= firstChar + 1 && c <= lastChar )
			{
				gfx.DrawSprite( curPos.x,curPos.y,MapGlyphRect( c ),surf,e );
			}
			curPos.x += glyphWidth;
		}
	}

	Vei2 GetCharSize() const;
private:
	RectI MapGlyphRect( char c ) const;
private:
	Surface surf;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	Color chroma;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};