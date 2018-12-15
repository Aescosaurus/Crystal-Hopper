#include "MouseTracker.h"
#include <cassert>

MouseTracker::MouseTracker( Mouse& mouse )
	:
	mouse( mouse )
{}

void MouseTracker::Update()
{
	if( mouse.LeftIsPressed() )
	{
		pressedLastFrame = true;
		canUnpress = false;

		if( lastMousePos == Vei2::Fake() )
		{
			lastMousePos = mouse.GetPos();
		}

		const Vei2 curMousePos = mouse.GetPos();

		// diff = Vec2( lastMousePos - curMousePos )
		// 	.GetNormalized();
		diff = Vec2( lastMousePos - curMousePos ) /
			50.0f;
	}
	else
	{
		if( canUnpress ) pressedLastFrame = false;
		else canUnpress = true;
		lastMousePos = Vei2::Fake();
	}
}

void MouseTracker::Draw( Graphics& gfx ) const
{
	if( lastMousePos != Vei2::Fake() )
	{
		gfx.DrawLine( Vec2( lastMousePos ),
			Vec2( mouse.GetPos() ),Colors::White );
	}
}

const Vec2& MouseTracker::GetDiff() const
{
	assert( diff != Vec2::Fake() );
	return( diff );
}

bool MouseTracker::Released() const
{
	return( !mouse.LeftIsPressed() &&
		diff != Vec2::Fake() &&
		pressedLastFrame );
}
