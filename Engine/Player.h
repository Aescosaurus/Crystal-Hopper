#pragma once

#include "MouseTracker.h"
#include "Graphics.h"
#include "Line.h"
#include "Circle.h"
#include "Surface.h"
#include "Codex.h"
#include <vector>
#include "Explosion.h"
#include "Timer.h"

class Player
{
public:
	Player( const Mouse& ms );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void CollideWith( const Line& l,float dt );
	void CollideWith( const Circle& c,float dt );
	void ClampSpeed();
	void Reset();
	void ResetLostPoints();

	// Returns true if there's a collision.
	bool CheckColl( const Line& l,float& dist ) const;
	// Also returns true on collision.
	bool CheckColl( const Circle& c,float& dist ) const;
	const Vec2& GetPos() const;
	int GetPointLoss() const;
private:
	const Mouse* pMouse;
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
	int pointsLost = 0;
	static constexpr int jumpPenalty = 50;
	CSurfPtr pGuySpr = SurfCodex::Fetch( "Images/Player.bmp" );
	std::vector<Explosion> explosionTrail;
	Timer explSpawnTime = 0.001f;
	static constexpr int nExplosionsPerJump = 5;
	int curJumpExplosions = 0;
	bool makingTrail = false;
};