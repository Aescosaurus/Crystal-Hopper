#include "Animation.h"
#include "Random.h"

Animation::Animation( int x,int y,int width,int height,int count,
	const Surface& sheet,float holdTime,bool repeating,Color chroma )
	:
	sheet( &sheet ),
	holdTime( holdTime ),
	chroma( chroma ),
	repeating( repeating )
{
	for( int i = 0; i < count; ++i )
	{
		frames.emplace_back( x + i * width,
			x + ( i + 1 ) * width,y,y + height );
	}
}

void Animation::Update( float dt )
{
	curFrameTime += dt;

	while( curFrameTime > holdTime && ( repeating || !finished ) )
	{
		curFrameTime -= holdTime;
		++frameIndex;
	}

	if( frameIndex >= frames.size() )
	{
		if( repeating )
		{
			curFrameTime = 0.0f;
			frameIndex = 0;
		}
		else
		{
			frameIndex = int( frames.size() ) - 1;
		}
		finished = true;
	}
}

void Animation::Reset()
{
	curFrameTime = 0.0f;
	frameIndex = 0;
	finished = false;
}

void Animation::SetFrame( int frame )
{
	frameIndex = frame;
}

bool Animation::IsFinished() const
{
	return( finished );
}

float Animation::GetPercent() const
{
	return( float( frameIndex ) / float( frames.size() ) );
}
