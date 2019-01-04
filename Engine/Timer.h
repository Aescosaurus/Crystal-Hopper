#pragma once

class Timer
{
public:
	Timer( float maxTime )
		:
		curTime( 0.0f ),
		maxTime( maxTime )
	{}
	void Update( float dt )
	{
		if( dt > 1.0f ) // That's HUGE, a 1 second long frame.
		{
			curTime += 1.0f / 60.0f;
			// TODO: Some way to let the user know this
			//  error happened(exception handling?)
		}
		curTime += dt;
	}
	void Reset()
	{
		curTime = 0.0f;
	}
	void SetNewMax( float newMax )
	{
		maxTime = newMax;
	}
	bool IsDone() const
	{
		return( curTime >= maxTime );
	}
private:
	float curTime;
	float maxTime;
};