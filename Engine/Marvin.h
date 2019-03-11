#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Codex.h"
#include "Animation.h"

class Marvin
{
public:
	Marvin( const Vei2& pos,float angle );

	void Update( float dt );
	// Always draw upright.
	void Draw( Graphics& gfx ) const;

	Circle GetCollider() const;
	const Vec2& GetVel() const;
public:
	static constexpr int pointValue = 100;
private:
	static constexpr int radius = 32;
	static constexpr float speed = 110.1f;
	Vec2 pos;
	Vec2 vel;
	Vec2 start;
	Vec2 end;
	CSurfPtr surfSheet = SurfCodex::Fetch( "Images/MarvinAnim.bmp" );
	Animation wobble;
};