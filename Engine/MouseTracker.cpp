#include "MouseTracker.h"
#include <cassert>

MouseTracker::MouseTracker( const Mouse& mouse )
	:
	pMouse( &mouse )
{}

void MouseTracker::Update( const Vec2& playerPos )
{
	if( pMouse->LeftIsPressed() )
	{
		pressedLastFrame = true;
		canUnpress = false;

		if( lastMousePos == Vei2::Fake() )
		{
			if( clickMovement ) lastMousePos = playerPos;
			else lastMousePos = pMouse->GetPos();
		}

		const Vei2 curMousePos = pMouse->GetPos();

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

void MouseTracker::Draw( Color c,Graphics& gfx ) const
{
	if( lastMousePos != Vei2::Fake() && !clickMovement )
	{
		gfx.DrawLine( Vec2( lastMousePos ),
			Vec2( pMouse->GetPos() ),c );
	}
}

void MouseTracker::SetClickMovement( bool enabled )
{
	clickMovement = enabled;
}

const Vec2& MouseTracker::GetDiff() const
{
	assert( diff != Vec2::Fake() );
	return( diff );
}

bool MouseTracker::Released() const
{
	return( !pMouse->LeftIsPressed() &&
		diff != Vec2::Fake() &&
		pressedLastFrame &&
		diff.GetLengthSq<float>() > 1.0f );
}

const Mouse& MouseTracker::GetMouse() const
{
	return( *pMouse );
}

bool MouseTracker::DiffIsReal() const
{
	return( diff != Vec2::Fake() );
}
