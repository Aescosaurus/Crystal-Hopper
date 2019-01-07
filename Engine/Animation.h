#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"
#include "Graphics.h"

class Animation
{
public:
	Animation( int x,int y,int width,int height,int count,
		const Surface& sheet,float holdTime,Color chroma = Colors::Magenta );
	Animation( const Animation& rhs );
	Animation& operator=( const Animation& rhs );

	void Update( float dt );
	template<typename Effect>
	void Draw( const Vei2& pos,Graphics& gfx,
		Effect eff,bool flipped = false ) const
	{
		Draw( pos,gfx,Graphics::GetScreenRect(),eff,
			Matrix::Rotation( 0.0f ),flipped );
	}
	template<typename Effect>
	void Draw( const Vei2& pos,Graphics& gfx,const RectI& clip,
		Effect eff,const Matrix& rotationMatrix,bool flipped ) const
	{
		gfx.DrawSprite( pos.x,pos.y,frames[frameIndex],
			clip,sheet,eff,rotationMatrix,flipped );
	}

	void Reset();
	void SetFrame( int frame );

	bool IsFinished() const;
private:
	const Surface& sheet;
	std::vector<RectI> frames;
	const float holdTime;
	const Color chroma;
	float curFrameTime = 0.0f;
	int frameIndex = 0;
	bool finished = false;
};