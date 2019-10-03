#pragma once

#include "Rect.h"
#include "Graphics.h"

// Point counter with lost points area that turns red and
//  slowly goes away.
class PointCounter
{
public:
	PointCounter( int maxPoints );

	void Update( int points,float dt );
	void Draw( Graphics& gfx ) const;
private:
	static constexpr int width = 170;
	static constexpr int height = 12;
	RectI area;
	int maxPoints = 0;
	int points = 0;
	float oldPoints = 0.0f;
	static constexpr float barMoveSpeed = 29.0f;
};