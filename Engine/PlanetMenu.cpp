#include "PlanetMenu.h"
#include "SpriteEffect.h"
#include <fstream>

PlanetMenu::PlanetMenu( const Vei2& pos,int planetNum,const std::string& img )
	:
	pos( pos ),
	planetNum( planetNum ),
	img( SurfCodex::Fetch( img + ".bmp" ) ),
	grayImg( SurfCodex::Fetch( img + "Gray.bmp" ) ),
	clickArea( pos,this->img->GetWidth(),this->img->GetHeight() )
{
	( this->pos ).x -= ( this->img )->GetWidth() / 2;
	( this->pos ).y -= ( this->img )->GetHeight() / 2;
	clickArea.MoveTo( this->pos );

	ReloadSaveInfo();
}

void PlanetMenu::Update( const Vei2& offset,const Vei2& mousePos,bool mouseDown )
{
	if( menuOpen )
	{
		for( auto& button : levelButtons )
		{
			if( button.Update( mousePos,mouseDown ) )
			{
				menuOpen = false;
			}
		}

		if( menuOpen && mouseDown && canClick &&
			!RectI{ menuPos,menuSize.x,menuSize.y }
			.ContainsPoint( mousePos ) )
		{
			menuOpen = false;
		}
	}
	else
	{
		if( clickArea.GetMovedBy( offset ).ContainsPoint( mousePos ) &&
			mouseDown && canClick && levelButtons.size() > 0 )
		{
			ReloadSaveInfo();
			menuOpen = true;
		}
	}

	canClick = !mouseDown;
}

void PlanetMenu::Draw( const Vei2& offset,Graphics& gfx ) const
{
	// TODO: Rotating planets?
	if( levelButtons.size() < 1 )
	{
		gfx.DrawSpriteNormal( pos.x + offset.x,pos.y + offset.y,
			*grayImg,SpriteEffect::Chroma{ Colors::Magenta } );

		gfx.DrawSpriteNormal( pos.x + offset.x + img->GetWidth() / 2 - lockIcon->GetWidth() / 2,
			pos.y + offset.y + img->GetHeight() / 2 - lockIcon->GetHeight() / 2,
			*lockIcon,SpriteEffect::Chroma{ Colors::Magenta } );
	}
	else
	{
		gfx.DrawSpriteNormal( pos.x + offset.x,pos.y + offset.y,
			*img,SpriteEffect::Chroma{ Colors::Magenta } );
	}
}

void PlanetMenu::DrawMenu( Graphics& gfx ) const
{
	if( menuOpen )
	{
		gfx.DrawRect( menuPos.x,menuPos.y,menuSize.x,menuSize.y,Colors::Gray );

		for( const auto& button : levelButtons )
		{
			button.DrawBackground( gfx );
		}
		for( const auto& stars : levelStars )
		{
			for( int i = 0; i < 5; ++i )
			{
				// gfx.DrawRect( stars.first.x + i * 16,stars.first.y,
				// 	16,16,Colors::Yellow );
				gfx.DrawSpriteNormal( stars.first.x + i * 16,
					stars.first.y,
					i < stars.second ? *filledStar : *emptyStar,
					SpriteEffect::Chroma{ Colors::Magenta } );
			}
		}
	}
}

void PlanetMenu::ReloadSaveInfo()
{
	levelButtons.clear();
	levelStars.clear();
	static constexpr Vei2 padding = menuSize.X() / 6 + menuSize.Y() / 3;
	static constexpr Vei2 starPadding = { menuSize.y / 10,menuSize.x / 10 };
	Vei2 buttonPos = menuPos + padding.X() + Vei2( Vec2( padding.Y() ) * 0.7f );

	std::ifstream in{ "Misc/Save.txt" };
	assert( in.good() );
	std::string temp = "";
	for( int i = 0; i < planetNum * 15; ++i ) std::getline( in,temp );
	for( int y = 0; y < 3; ++y )
	{
		for( int x = 0; x < 5; ++x )
		{
			if( temp != "0" )
			{
				levelButtons.emplace_back( Button{
					buttonPos + padding.X() * x + padding.Y() * y,
					std::to_string( y * 5 + x + 1 ) } );

				std::getline( in,temp );
				levelStars.emplace_back( std::make_pair<Vei2,int>(
					buttonPos + padding.X() * x + padding.Y() * y - starPadding,
					std::stoi( temp ) ) );
			}
			else break;
		}
	}
}

int PlanetMenu::GetReaction()
{
	for( int i = 0; i < int( levelButtons.size() ); ++i )
	{
		if( levelButtons[i].IsPressed() )
		{
			levelButtons[i].Reset();
			return( i + 1 + planetNum * 15 );
		}
	}
	return( 0 );
}