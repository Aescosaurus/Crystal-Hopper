#pragma once

class Timer
{
public:
	Timer( float maxTime )
		:
		curTime( 0.0f ),
		maxTime( maxTime )
	{}
	bool Update( float dt )
	{
		curTime += dt;

		return( IsDone() );
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
	int GetPercent() const
	{
		return( int( ( curTime / maxTime ) * 100.0f ) );
	}
private:
	float curTime;
	float maxTime;
};