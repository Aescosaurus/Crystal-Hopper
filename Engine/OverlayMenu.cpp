#include "OverlayMenu.h"

void OverlayMenu::Update( const Keyboard& kbd,const Mouse& mouse )
{
	const auto& msPos = mouse.GetPos();
	const auto msDown = mouse.LeftIsPressed();

	if( !open )
	{
		if( menuOpener.Update( msPos,msDown ) ||
			kbd.KeyIsPressed( VK_SPACE ) )
		{
			open = true;
		}
	}
	else
	{
		if( resume.Update( msPos,msDown ) ) open = false;
		restart.Update( msPos,msDown );
		quit.Update( msPos,msDown );
	}
}

void OverlayMenu::Draw( Graphics& gfx ) const
{
	if( !open )
	{
		menuOpener.Draw( gfx );
	}
	else
	{
		gfx.DrawRect( pos.x,pos.y,size.x,size.y,Colors::Gray );

		resume.Draw( gfx );
		restart.Draw( gfx );
		quit.Draw( gfx );
	}
}

void OverlayMenu::Close()
{
	open = false;
	menuOpener.Reset();
	resume.Reset();
	restart.Reset();
	quit.Reset();
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
