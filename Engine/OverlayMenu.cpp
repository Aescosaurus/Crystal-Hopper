#include "OverlayMenu.h"
#include "SpriteEffect.h"

void OverlayMenu::Update( const Keyboard& kbd,const Mouse& mouse )
{
	const auto dt = ft.Mark();

	const auto& msPos = mouse.GetPos();
	const auto msDown = mouse.LeftIsPressed();

	if( !kbd.KeyIsPressed( VK_ESCAPE ) ) canEscape = true;

	if( canEscape && kbd.KeyIsPressed( VK_ESCAPE ) )
	{
		open = !open;
		canEscape = false;
		menuBGAnim.Reset();
	}

	if( !open )
	{
		if( menuOpener.Update( msPos,msDown ) )
		{
			open = true;
		}
	}
	else
	{
		if( resume.Update( msPos,msDown ) ) Close();
		restart.Update( msPos,msDown );
		quit.Update( msPos,msDown );

		menuBGAnim.Update( dt );
	}
}

void OverlayMenu::Draw( Graphics& gfx ) const
{
	if( !open )
	{
		// return; // For no ui

		menuOpener.Draw( gfx );
	}
	else
	{
		// gfx.DrawRect( pos.x,pos.y,size.x,size.y,Colors::Gray );
		// gfx.DrawSpriteNormal( pos.x,pos.y,*menuBGSpr,
		// 	SpriteEffect::Chroma{} );
		menuBGAnim.Draw( pos,gfx,SpriteEffect::Chroma{} );

		if( menuBGAnim.IsFinished() )
		{
			resume.Draw( gfx );
			restart.Draw( gfx );
			quit.Draw( gfx );
		}
	}
}

void OverlayMenu::Close()
{
	open = false;
	menuOpener.Reset();
	resume.Reset();
	restart.Reset();
	quit.Reset();
	menuBGAnim.Reset();
}

bool OverlayMenu::IsOpen() const
{
	return( open );
}

bool OverlayMenu::WillResume() const
{
	return( resume.IsPressed() );
}

bool OverlayMenu::WillRestart() const
{
	return( restart.IsPressed() );
}

bool OverlayMenu::WillExit() const
{
	return( quit.IsPressed() );
}
