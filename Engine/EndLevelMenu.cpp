#include "EndLevelMenu.h"
#include "SpriteEffect.h"

void EndLevelMenu::Update( const Mouse& mouse )
{
	retry.Update( mouse.GetPos(),mouse.LeftIsPressed() );
	menu.Update( mouse.GetPos(),mouse.LeftIsPressed() );
	if( !lost )
	{
		resume.Update( mouse.GetPos(),mouse.LeftIsPressed() );
	}
}

void EndLevelMenu::Draw( Graphics& gfx ) const
{
	// gfx.DrawRect( pos.x,pos.y,size.x,size.y,Colors::Gray );
	gfx.DrawSpriteNormal( pos.x,pos.y,*menuBGSpr,
		SpriteEffect::Chroma{} );

	retry.Draw( gfx );
	menu.Draw( gfx );
	if( !lost )
	{
		resume.Draw( gfx );
	}

	// All this work just to draw x/5 stars.
	// const float starRadius = 45.0f;
	const auto starSize = Vei2{ filledStar->GetWidth(),
		filledStar->GetHeight() };
	const int center = Graphics::ScreenWidth / 2;
	const int start = center - ( scoreTiers / 2 ) *
		int( starSize.x );
	for( int i = 0; i < scoreTiers; ++i )
	{
		// const auto starCol = stars >= i + 1
		// 	? Colors::Yellow : Colors::Black;
		// gfx.DrawStar( start + int( starRadius ) * 2 * i,190,
		// 	starRadius,starCol );

		const Vei2 drawPos = Vei2{ start +
			int( starSize.x * 1.25f ) * i,210 } -starSize;
		gfx.DrawSprite( drawPos.x,drawPos.y,
			stars >= i + 1 && !lost
			? *filledStar : *emptyStar,
			SpriteEffect::Chroma{ Colors::Magenta } );
	}

	luckyPixel->DrawText( "Points:" + std::to_string( points ),
		Vei2{ 350,220 },Colors::Yellow,gfx );
}

void EndLevelMenu::UpdatePoints( float percent,int points )
{
	if( lost )
	{
		percent = 0.0f;
		points = 0;
	}
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

void EndLevelMenu::Lose()
{
	lost = true;
}

void EndLevelMenu::UnLose()
{
	lost = false;
}

void EndLevelMenu::Reset()
{
	retry.Reset();
	resume.Reset();
	menu.Reset();
}

bool EndLevelMenu::PressedRetry() const
{
	return( retry.IsPressed() );
}

bool EndLevelMenu::PressedContinue() const
{
	return( resume.IsPressed() );
}

bool EndLevelMenu::PressedMenu() const
{
	return( menu.IsPressed() );
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

const int* EndLevelMenu::GetStarWeights() const
{
	return( &starBracketPercents[0] );
}

bool EndLevelMenu::HasLost() const
{
	return( lost );
}
