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

	// All this work just to draw x/5 stars.
	const float starRadius = 45.0f;
	const int center = Graphics::ScreenWidth / 2;
	const int start = center - ( scoreTiers / 2 ) *
		int( starRadius ) * 2;
	for( int i = 0; i < scoreTiers; ++i )
	{
		const auto starCol = stars >= i + 1
			? Colors::Yellow : Colors::Black;
		gfx.DrawStar( start + int( starRadius ) * 2 * i,190,
			starRadius,starCol );
	}


}

void EndLevelMenu::UpdatePoints( float percent,int points )
{
	this->points = points;
	stars = Points2Stars( percent );
}

void EndLevelMenu::UpdateStarWeights( const std
	::vector<int>& weights )
{
	assert( weights.size() == 5 );
	for( int i = 0; i < 5; ++i )
	{
		starBracketPercents[i] = weights[i];
	}
}

bool EndLevelMenu::PressedRetry() const
{
	return( retry.IsPressed() );
}

bool EndLevelMenu::PressedContinue() const
{
	return( resume.IsPressed() );
}

int EndLevelMenu::Points2Stars( float percent ) const
{
	const int val = int( percent * 100.0f );
	for( int i = scoreTiers - 1; i >= 0; --i )
	{
		if( val > starBracketPercents[i] ) return( i + 1 );
	}
	return( 1 );
}
