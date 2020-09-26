#include "MouseTracker.h"
#include <cassert>
#include "SpriteEffect.h"

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

		if( !clickMovement )
		{
			if( lastMousePos == Vei2::Fake() )
			{
				clickSound->Play( 0.7f );
				/*if( clickMovement ) lastMousePos = playerPos;
				else */lastMousePos = pMouse->GetPos();
			}
		}
		else
		{
			lastMousePos = playerPos;
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
		else
		{
			clickSound->StopAll();
			releaseSound->Play( 0.6f );
			canUnpress = true;
		}
		lastMousePos = Vei2::Fake();
	}
}

void MouseTracker::Draw( Color c,Graphics& gfx ) const
{
	if( lastMousePos != Vei2::Fake() && !clickMovement )
	{
		// gfx.DrawLine( Vec2( lastMousePos ),
		// 	Vec2( pMouse->GetPos() ),c );

		const auto diff = Vec2( lastMousePos - pMouse->GetPos() );
		const auto len = diff.GetLength<float>();
		if( len > 0.0f )
		{
			const auto norm = diff.GetNormalized();
			auto pos = Vec2( lastMousePos );
			static constexpr auto step = 5;
			for( int i = 0; i < int( len ) / step; ++i )
			{
				gfx.DrawSprite( int( pos.x ),int( pos.y ),
					c == Colors::White ? *whiteSpr : *redSpr,
					SpriteEffect::SafeChroma{ Colors::Magenta } );
				pos -= norm * step;
			}
		}
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

bool MouseTracker::ClickMovement() const
{
	return( clickMovement );
}
