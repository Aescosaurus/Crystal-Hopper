#pragma once

#include "MouseTracker.h"
#include "Graphics.h"
#include "Line.h"
#include "Circle.h"

class Player
{
public:
	Player( const Mouse& ms );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void CollideWith( const Line& l,float dt );
	void CollideWith( const Circle& c,float dt );
	void ClampSpeed();
	void ResetPos();

	// Returns true if there's a collision.
	bool CheckColl( const Line& l,float& dist ) const;
	// Also returns true on collision.
	bool CheckColl( const Circle& c,float& dist ) const;
	const Vec2& GetPos() const;
private:
	MouseTracker mt;
	static constexpr int size = 24; // Diameter, not radius.
	Vec2 pos;
	Vec2 vel;
	static constexpr float velDecay = 0.995f;
	static constexpr float speed = 2.2f;
	float curGrav = 0.0f;
	static constexpr float gravAcc = 0.14f; // From 0.14.
	static constexpr float bounceLoss = 0.71f;
	// Make sure maxSpeed is less than size for hit tests.
	static constexpr float maxSpeed = float( size / 2 - 1 );
	bool canJump = true;
};