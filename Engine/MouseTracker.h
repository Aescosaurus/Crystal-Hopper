#pragma once

#include "Mouse.h"
#include "Vec2.h"
#include "Graphics.h"

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
private:
	const Mouse* pMouse;
	Vei2 lastMousePos;
	Vec2 diff = Vec2::Fake();
	bool pressedLastFrame = false;
	bool canUnpress = false;
	bool clickMovement = false;
};