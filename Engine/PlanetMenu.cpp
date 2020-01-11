#include "PlanetMenu.h"
#include "SpriteEffect.h"

PlanetMenu::PlanetMenu( const Vei2& pos,const std::string& img )
	:
	pos( pos ),
	img( SurfCodex::Fetch( img ) ),
	clickArea( pos,this->img->GetWidth(),this->img->GetHeight() )
{
	( this->pos ).x -= ( this->img )->GetWidth() / 2;
	( this->pos ).y -= ( this->img )->GetHeight() / 2;
	clickArea.MoveTo( this->pos );

	static constexpr Vei2 padding = menuSize.X() / 6 + menuSize.Y() / 4;
	Vei2 buttonPos = menuPos + padding;
	for( int y = 0; y < 3; ++y )
	{
		for( int x = 0; x < 5; ++x )
		{
			levelButtons.emplace_back( Button{
				buttonPos + padding.X() * x + padding.Y() * y,
				std::to_string( y * 5 + x + 1 ) } );
		}
	}
}

void PlanetMenu::Update( const Vei2& offset,const Vei2& mousePos,bool mouseDown )
{
	if( menuOpen )
	{
		for( auto& button : levelButtons )
		{
			button.Update( mousePos,mouseDown );
		}

		if( mouseDown && !RectI{ menuPos,menuSize.x,menuSize.y }
			.ContainsPoint( mousePos ) )
		{
			menuOpen = false;
		}
	}
	else
	{
		if( clickArea.GetMovedBy( offset ).ContainsPoint( mousePos ) &&
			mouseDown && canClick )
		{
			menuOpen = true;
		}

		canClick = !mouseDown;
	}
}

void PlanetMenu::Draw( const Vei2& offset,Graphics& gfx ) const
{
	if( menuOpen )
	{
		gfx.DrawRect( menuPos.x,menuPos.y,menuSize.x,menuSize.y,Colors::Gray );

		for( const auto& button : levelButtons )
		{
			button.DrawBackground( gfx );
		}
	}
	else
	{
		// TODO: Rotating planets?
		gfx.DrawSpriteNormal( pos.x + offset.x,pos.y + offset.y,
			*img,SpriteEffect::Chroma{ Colors::Magenta } );
	}
}

int PlanetMenu::GetReaction() const
{
	for( int i = 0; i < int( levelButtons.size() ); ++i )
	{
		if( levelButtons[i].IsPressed() )
		{
			return( i + 1 );
		}
	}
	return( 0 );
}
