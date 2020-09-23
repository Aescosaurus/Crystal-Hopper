#pragma once

#include "Sound.h"

// BS class to dance around const.
class Audio
	:
	public Sound
{
public:
	Audio( const std::string& src,bool loop = false )
		:
		aud( src,loop )
	{}

	virtual void Play( float vol = 1.0f ) const
	{
		aud.Play( 1.0f,vol * globalVol );
	}
	void Stop() const
	{
		aud.StopOne();
	}
	void StopAll() const
	{
		aud.StopAll();
	}
public:
	static float globalVol;
private:
	mutable Sound aud;
};