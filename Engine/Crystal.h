#pragma once

#include "Vec2.h"

class Crystal
{
public:
	// Collect these to complete the level.
	Crystal( const Vec2& pos );
private:
	Vec2 pos;
};