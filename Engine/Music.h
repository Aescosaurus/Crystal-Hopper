#pragma once

#include "Audio.h"

// BS class to dance around codex.
class Music
	:
	public Audio
{
public:
	Music( const std::string& src )
		:
		Audio( src,true )
	{}

	void Play( float vol = 1.0f ) const override
	{
		Audio::Play( vol * globalMVol );
	}
public:
	static float globalMVol;
};