#include "Animation.h"

Animation::Animation( int x,int y,int width,int height,int count,
	const Surface& sheet,float holdTime,Color chroma )
	:
	sheet( &sheet ),
	holdTime( holdTime ),
	chroma( chroma )
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

	while( curFrameTime > holdTime )
	{
		curFrameTime -= holdTime;
		++frameIndex;
	}

	if( frameIndex >= frames.size() )
	{
		curFrameTime = 0.0f;
		frameIndex = 0;
		finished = true;
	}
}

void Animation::Reset()
{
	curFrameTime = 0.0f;
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
