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
		curTime += dt;
	}
	void Reset()
	{
		curTime = 0.0f;
	}
	void ResetRng( float minusAmount )
	{
		curTime = minusAmount;
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