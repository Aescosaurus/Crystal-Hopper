#pragma once

#include "Mouse.h"
#include "Vec2.h"
#include "Graphics.h"

class MouseTracker
{
public:
	MouseTracker( const Mouse& mouse );

	void Update();
	void Draw( Color c,Graphics& gfx ) const;

	const Vec2& GetDiff() const;
	bool Released() const;
private:
	const Mouse* pMouse;
	Vei2 lastMousePos;
	Vec2 diff;
	bool pressedLastFrame = false;
	bool canUnpress = false;
};