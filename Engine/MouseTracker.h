#pragma once

#include "Mouse.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Codex.h"

class MouseTracker
{
public:
	MouseTracker( const Mouse& mouse );

	void Update( const Vec2& playerPos );
	void Draw( Color c,Graphics& gfx ) const;

	void SetClickMovement( bool enabled );

	const Vec2& GetDiff() const;
	bool Released() const;
	const Mouse& GetMouse() const;
	bool DiffIsReal() const;
	bool ClickMovement() const;
private:
	const Mouse* pMouse;
	Vei2 lastMousePos;
	Vec2 diff = Vec2::Fake();
	bool pressedLastFrame = false;
	bool canUnpress = true; // From false (maybe broke something).
	bool clickMovement = false;

	CSurfPtr whiteSpr = SurfCodex::Fetch( "Images/LineWhite.bmp" );
	CSurfPtr redSpr = SurfCodex::Fetch( "Images/LineRed.bmp" );

	CSoundPtr clickSound = SoundCodex::Fetch( "Audio/Mouse1.wav" );
	CSoundPtr releaseSound = SoundCodex::Fetch( "Audio/Mouse2.wav" );
};