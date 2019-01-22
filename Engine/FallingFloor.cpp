#include "FallingFloor.h"
#include "Player.h"
#include "SpriteEffect.h"

FallingFloor::FallingFloor( const Vec2& pos,float angle,float gravAcc )
	:
	Floor( pos,angle,SurfCodex::Fetch( "Images/FallingPlatform.bmp" ) ),
	gravAcc( gravAcc )
{}

void FallingFloor::Update( float dt )
{
	if( center.y < float( Graphics::ScreenHeight * 2 ) &&
		falling )
	{
		grav += gravAcc;
		center.y += grav;
		MoveBy( Vec2{ 0.0f,grav } );
	}
}

void FallingFloor::Draw( Graphics& gfx ) const
{
	const auto drawPos = GetDrawPos();

	gfx.DrawSprite( drawPos.x,drawPos.y,
		img->GetRect(),Rect( Graphics::GetScreenRect()
		.GetExpanded( int( size.x ) ) ),*img,
		SpriteEffect::SafeChroma{ Colors::Magenta },
		rotationMatrix );
}

bool FallingFloor::HandleColl( Player& guy,float dt )
{
	// Don't collide with player if you're falling!
	if( !falling )
	{
		if( Floor::HandleColl( guy,dt ) )
		{
			falling = true;
			grav -= jumpPower;
			return( true );
		}
	}
	return( false );
}
