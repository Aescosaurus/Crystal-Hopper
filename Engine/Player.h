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
	Player( const Mouse& ms,std::vector<std::unique_ptr<Explosion>>& explosions,float grav );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void CollideWith( const Line& l,float dt );
	void CollideWith( const Circle& c,float dt );
	void ClampSpeed();
	void Reset( std::vector<std::unique_ptr<Explosion>>& explosions,float grav );
	void ResetLostPoints();
	void DisableJumping();
	void AddVelocity( const Vec2& otherVel,float dt );
	// Keep the player inside the play area.
	void DontHitWalls( float dt );
	// Apply invincibility frames.
	void ApplyInvul();
	void FlipGravity();
	void FlipSlowPercent();
	void RotateGravity();

	// Returns true if there's a collision.
	bool CheckColl( const Line& l,float& dist ) const;
	// Also returns true on collision.
	bool CheckColl( const Circle& c,float& dist ) const;
	const Vec2& GetPos() const;
	int GetPointLoss() const;
	bool HasJumped() const;
	bool IsInvincible() const;
	Vec2 GetCurGravity() const;
private:
	const Mouse* pMouse;
	MouseTracker mt;
	static constexpr int size = 24; // Diameter, not radius.
	Vec2 pos;
	Vec2 vel;
	static constexpr float velDecay = 0.995f;
	static constexpr float speed = 2.2f;
	float curGrav = 0.0f;
	float gravAcc;
	static constexpr float bounceLoss = 0.71f;
	// Make sure maxSpeed is less than size for hit tests.
	static constexpr float maxSpeed = float( size / 2 - 1 );
	bool canJump = true;
	int pointsLost = 0;
	static constexpr int jumpPenalty = 50;
	CSurfPtr pGuySpr = SurfCodex::Fetch( "Images/Player.bmp" );
	std::vector<std::unique_ptr<Explosion>>* explosions;
	Timer explSpawnTime = 0.03f;
	static constexpr int nExplosionsPerJump = 5;
	int curJumpExplosions = 0;
	bool makingTrail = false;
	CSurfPtr pArrowSurf = SurfCodex::Fetch( "Images/PlayerArrow.bmp" );
	bool hasJumped = false;
	bool jumpDisabled = false;
	Matrix rotMatrix = Matrix::Rotation( 0.0f );
	bool invincible = false;
	Timer invincibilityFrames = 2.5f;
	Vec2 gravScale = Vec2{ 0.0f,1.0f };
	float slowPercent = 1.0f;
};