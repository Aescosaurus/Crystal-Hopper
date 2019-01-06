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

	void Draw( Graphics& gfx ) const;

	void MoveBy( const Vec2& moveAmount );

	const std::vector<Line>& GetLines() const;
	const std::vector<Circle>& GetCorners() const;
private:
	Vec2 RotatePoint( const Vec2& point,
		const Vec2& about,const Matrix& rotMat ) const;
private:
	static constexpr Vec2 size = { 160.0f,60.0f };
	static constexpr float cornerSize = 1.1f;
	Vei2 center;
	std::vector<Line> lines;
	std::vector<Circle> corners;
	const Matrix rotationMatrix;
	CSurfPtr img = SurfCodex::Fetch( "Images/Platform.bmp" );
};