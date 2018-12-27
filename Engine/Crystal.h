#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"

// Collect these to complete the level.
class Crystal
{
public:
	Crystal( const Vec2& pos );

	void Draw( Graphics& gfx ) const;

	void Collect();

	Circle GetCollider() const;
	bool WillRemove() const;
private:
	static constexpr int radius = 24;
	Vec2 pos;
	bool collected = false;
};