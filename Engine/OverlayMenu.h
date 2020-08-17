#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Button.h"

class OverlayMenu
{
public:
	void Update( const Keyboard& kbd,const Mouse& mouse );
	void Draw( Graphics& gfx ) const;

	void Close();

	bool IsOpen() const;
	bool WillResume() const;
	bool WillRestart() const;
	bool WillExit() const;
private:
	const Vei2 size = Vei2( Vec2( Graphics::ScreenSize ) / 1.5f );
	const Vei2 pos = Graphics::GetCenter() - size / 2;
	bool open = false;
	bool canEscape = false;
	Button menuOpener = Button{ Vei2{ Graphics::ScreenWidth - 35,35 },"~" };
	Button resume = Button{ Graphics::GetCenter() - Vei2{ 0,100 },"Resume" };
	Button restart = Button{ Graphics::GetCenter() - Vei2{ 0,20 },"Restart" };
	Button quit = Button{ Graphics::GetCenter() + Vei2{ 0,60 },"Menu" };

	CSurfPtr menuBGSpr = SurfCodex::Fetch( "Images/MenuBG.bmp" );
};