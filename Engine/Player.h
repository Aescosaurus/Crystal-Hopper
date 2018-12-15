#pragma once

#include "MouseTracker.h"
#include "Graphics.h"

class Player
{
public:
	Player( MouseTracker& mt );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;
private:
	MouseTracker& mt;
	static constexpr Vei2 size = { 16,16 };
	Vec2 pos;
	Vec2 vel;
	static constexpr float velDecay = 0.995f;
	static constexpr float speed = 3.0f;
	float curGrav = 0.0f;
	static constexpr float gravAcc = 0.14f;
	static constexpr float bounceLoss = 0.71f;
};