#pragma once

#include "MouseTracker.h"
#include "Graphics.h"
#include "Line.h"

class Player
{
private:
	enum class Dir
	{
		Up,
		Down,
		Left,
		Right
	};
public:
	Player( MouseTracker& mt );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void CollideWith( const Line& l );

	// Returns true if there's a collision.
	bool CheckColl( const Line& l,float& dist ) const;
private:
	MouseTracker& mt;
	static constexpr int size = 16;
	Vec2 pos;
	Vec2 vel;
	static constexpr float velDecay = 0.995f;
	static constexpr float speed = 3.0f;
	float curGrav = 0.0f;
	static constexpr float gravAcc = 0.14f;
	static constexpr float bounceLoss = 0.71f;
};