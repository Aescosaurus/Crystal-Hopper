#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Animation.h"
#include "Codex.h"

// Turret that sticks to platforms or walls and shoots
//  bullets at the player periodically (which make
//  the player lose lots of points).
class MarsTurret
{
public:
	MarsTurret( const Vec2& pos,float angle );

	void Update( const Vec2& playerPos,float dt );
	void Draw( Graphics& gfx ) const;

	Circle GetColl() const;
private:
	static constexpr int radius = 32;
	Vec2 pos;
	Matrix rotMat;
	CSurfPtr pSurfSheet = SurfCodex::Fetch( "Images/MarsTurretAnim.bmp" );
	Animation baseAnim;
	Animation topAnim;
	// Timer shotRefire
};