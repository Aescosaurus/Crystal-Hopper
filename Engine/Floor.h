#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <vector>
#include "Line.h"
#include "Matrix.h"
#include "Circle.h"
#include "Surface.h"
#include "Codex.h"

class Floor
{
public:
	Floor( const Vec2& pos,float angle );

	// Children can override this for their anims or w/e.
	virtual void Update( float dt ) {}
	virtual void Draw( Graphics& gfx ) const;

	// No idea why I didn't const this but there was
	//  probably a good reason so I'll leave it.  Returns
	//  true on collision with player.
	virtual bool HandleColl( class Player& guy,float dt );

	const std::vector<Line>& GetLines() const;
	const std::vector<Circle>& GetCorners() const;
protected:
	Floor( const Vec2& pos,float angle,CSurfPtr img );

	void MoveBy( const Vec2& amount );

	Vei2 GetDrawPos() const;
private:
	Vec2 RotatePoint( const Vec2& point,
		const Vec2& about,const Matrix& rotMat ) const;
protected:
	CSurfPtr img;
	static constexpr Vec2 size = { 160.0f,60.0f };
	static constexpr float cornerSize = 1.1f;
	Vec2 center;
	std::vector<Line> lines;
	std::vector<Circle> corners;
	const Matrix rotationMatrix;
};