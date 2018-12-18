#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <vector>
#include "Line.h"
#include "Matrix.h"

class Floor
{
public:
	Floor( const Vec2& pos,const Vec2& size,float angle );

	void Draw( Graphics& gfx ) const;

	void MoveBy( const Vec2& moveAmount );

	const std::vector<Line>& GetLines() const;
private:
	Vec2 RotatePoint( const Vec2& point,
		const Vec2& about,const Matrix& rotMat ) const;
private:
	// Vec2 ul;
	// Vec2 ur;
	// Vec2 dl;
	// Vec2 dr;
	std::vector<Line> lines;
};