#pragma once

#include <vector>
#include "Animation.h"
#include "Graphics.h"
#include "SpriteEffect.h"

class SpiffyBG
{
public:
	class Layer
	{
	public:
		Layer( const Animation& anim,Vec2 pos,Vec2 vel,Vec2 resetPos,float alpha = 1.0f )
			:
			anim( anim ),
			pos( pos * 4.0f ),
			initPos( pos * 4.0f ),
			vel( vel ),
			resetPos( resetPos * 4.0f ),
			alpha( alpha )
		{}
	public:
		Animation anim;
		Vec2 pos;
		Vec2 initPos;
		Vec2 vel;
		Vec2 resetPos;
		float alpha;
	};
public:
	SpiffyBG( const std::vector<Layer>& anims )
		:
		anims( anims )
	{}

	void Update( float dt )
	{
		for( auto& layer : anims )
		{
			layer.anim.Update( dt );

			if( ( layer.pos - layer.resetPos ).GetLengthSq<float>() <
				( ( layer.pos + layer.vel * dt ) - layer.resetPos ).GetLengthSq<float>() )
			{
				layer.pos = layer.initPos;
			}

			layer.pos += layer.vel * dt;
		}
	}
	void Draw( Graphics& gfx ) const
	{
		for( const auto& layer : anims )
		{
			layer.anim.Draw( layer.pos,gfx,
				SpriteEffect::ChromaFade{ Colors::Magenta,layer.alpha } );
		}
	}
private:
	std::vector<Layer> anims;
};