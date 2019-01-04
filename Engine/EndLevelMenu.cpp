#include "EndLevelMenu.h"

void EndLevelMenu::Update( const Mouse& mouse )
{
	retry.Update( mouse.GetPos(),mouse.LeftIsPressed() );
	resume.Update( mouse.GetPos(),mouse.LeftIsPressed() );
}

void EndLevelMenu::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( pos.x,pos.y,size.x,size.y,Colors::Gray );

	retry.Draw( gfx );
	resume.Draw( gfx );
}

bool EndLevelMenu::PressedRetry() const
{
	return( retry.IsPressed() );
}

bool EndLevelMenu::PressedContinue() const
{
	return( resume.IsPressed() );
}

int EndLevelMenu::Points2Stars( int points )
{
	for( int i = scoreTiers - 1; i >= 0; --i )
	{
		if( points > starBracketPercents[i] ) return( i );
	}
	return( starBracketPercents[0] );
}
