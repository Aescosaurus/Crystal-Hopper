#pragma once

#include "Vec2.h"
#include <vector>
#include "Line.h"
#include "Matrix.h"
#include "Player.h"
#include "Graphics.h"
#include "Circle.h"
#include "Codex.h"
#include "Surface.h"

// I guess it's a stalactite if it's hanging from the roof,
//  but what if it's on the side???
class Stalagmite
{
public:
	Stalagmite( const Vec2& pos,float angle );

	void Draw( Graphics& gfx ) const;

	bool HandleColl( Player& guy,float dt ) const;
private:
	Vec2 RotatePoint( const Vec2& point,
		const Vec2& about,const Matrix& rotMat ) const;
public:
	static constexpr int pointValue = 100;
private:
	static constexpr Vec2 size = { 60.0f,160.0f };
	static constexpr float cornerSize = 1.1f;
	Vec2 center;
	std::vector<Line> lines;
	std::vector<Circle> corners;
	Matrix rotationMatrix;
	CSurfPtr img = SurfCodex::Fetch( "Images/Stalagmite.bmp" );
};