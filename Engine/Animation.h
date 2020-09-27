#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"
#include "Graphics.h"

class Animation
{
public:
	Animation( int x,int y,int width,int height,int count,
		const Surface& sheet,float holdTime,bool repeating = true,Color chroma = Colors::Magenta );

	void Update( float dt );
	template<typename Effect>
	void Draw( const Vei2& pos,Graphics& gfx,
		Effect eff,bool flipped = false ) const
	{
		gfx.DrawSpriteNormal( pos.x,pos.y,
			frames[frameIndex],*sheet,eff,flipped );
	}
	template<typename Effect>
	void DrawRotated( const Vei2& pos,Graphics& gfx,
		Effect eff,Matrix rotation ) const
	{
		gfx.DrawSprite( pos.x,pos.y,frames[frameIndex],
			*sheet,eff,rotation );
	}

	void Reset();
	void SetFrame( int frame );

	bool IsFinished() const;
	float GetPercent() const;
	static Animation Single( const std::string& img );
private:
	const Surface* sheet;
	std::vector<RectI> frames;
	/*const */float holdTime;
	/*const */Color chroma;
	float curFrameTime = 0.0f;
	int frameIndex = 0;
	bool finished = false;
	bool repeating;
};