#pragma once

#include "Vec2.h"
#include <string>
#include "Codex.h"
#include "Mouse.h"
#include "Graphics.h"
#include "SpriteEffect.h"

class Slider
{
public:
	Slider( const Vei2& pos,const std::string& text,float defaultVal = 0.5f )
		:
		pos( pos ),
		text( text ),
		textWidth( int( text.length() + 1 ) * ( font->GetCharSize().x ) ),
		handArea( pos,pos + hand->GetSize() ),
		minX( pos.x + textWidth - handArea.GetWidth() / 2 ),
		maxX( pos.x + bg->GetWidth() + textWidth - handArea.GetWidth() / 2 )
	{
		handArea.MoveTo( Vei2{ minX + int( float( maxX - minX ) * defaultVal ),handArea.top } );
	}

	void Update( const Mouse& mouse )
	{
		if( mouse.LeftIsPressed() )
		{
			if( handArea.ContainsPoint( mouse.GetPos() ) )
			{
				dragging = true;
			}
		}
		else dragging = false;

		if( dragging )
		{
			auto newX = mouse.GetPos().x - handArea.GetWidth() / 2;
			if( newX < minX ) newX = minX;
			if( newX > maxX ) newX = maxX;
			handArea.MoveTo( Vei2{ newX,handArea.top } );
		}
	}

	void Draw( Graphics& gfx ) const
	{
		gfx.DrawSpriteNormal( pos.x + textWidth,pos.y,
			*bg,SpriteEffect::Chroma{} );
		gfx.DrawSpriteNormal( handArea.left,handArea.top,
			*hand,SpriteEffect::Chroma{} );
		font->DrawText( text,pos,Colors::LightGray,gfx );
	}

	void Read( const std::string& line )
	{
		std::string val = "";
		float percent = 0.0f;
		bool writingVal = false;
		for( char c : line )
		{
			if( c == ':' ) writingVal = true;
			else if( writingVal && c != ' ' ) val += c;
		}
		try
		{
			percent = std::stof( val );
		}
		catch( ... ) {}

		handArea.MoveTo( Vei2{ Percent2X( GetPercent() ),handArea.top } );
	}

	std::string Write() const
	{
		return( text + ": " + std::to_string( GetPercent() ) );
	}
	float GetPercent() const
	{
		return( float( handArea.GetCenter().x - minX ) / float( maxX - minX ) );
	}
	int Percent2X( float percent )
	{
		return( int( float( maxX - minX ) * percent ) + minX );
	}
private:
	CFontPtr font = FontCodex::Fetch( "Fonts/LuckyPixel6x9.bmp" );
	CSurfPtr bg = SurfCodex::Fetch( "Images/SliderBG.bmp" );
	CSurfPtr hand = SurfCodex::Fetch( "Images/SliderHand.bmp" );
	Vei2 pos;
	std::string text;
	int textWidth;
	RectI handArea;
	bool dragging = false;
	int minX = 0;
	int maxX = 0;
};