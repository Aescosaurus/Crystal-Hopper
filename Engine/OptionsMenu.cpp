#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
	Load();
}

void OptionsMenu::Update( const Mouse& mouse )
{
	const auto& msPos = mouse.GetPos();
	const auto msDown = mouse.LeftIsPressed();

	menuButton.Update( msPos,msDown );

	invertControls.Update( msPos,msDown );
	clickMovement.Update( msPos,msDown );
	musicSlider.Update( mouse );
	soundSlider.Update( mouse );
}

void OptionsMenu::Draw( Graphics& gfx ) const
{
	menuButton.Draw( gfx );

	invertControls.Draw( gfx );
	clickMovement.Draw( gfx );

	musicSlider.Draw( gfx );
	soundSlider.Draw( gfx );

	font->DrawText( "Options:",Vei2{ 50,50 },Colors::LightGray,gfx );
}

void OptionsMenu::Save()
{
	std::ofstream out{ saveFileName };
	assert( out.good() );

	out << invertControls.Write() << '\n';
	out << clickMovement.Write() << '\n';
	out << musicSlider.Write() << '\n';
	out << soundSlider.Write() << '\n';
}

void OptionsMenu::Load()
{
	auto read_line = []( std::ifstream& in )
	{
		std::string temp;
		std::getline( in,temp );
		return( temp );
	};

	std::ifstream in{ saveFileName };

	if( !in.good() )
	{
		Save();
	}
	else
	{
		invertControls.Read( read_line( in ) );
		clickMovement.Read( read_line( in ) );
		musicSlider.Read( read_line( in ) );
		soundSlider.Read( read_line( in ) );
	}
}

bool OptionsMenu::BackToMenu() const
{
	return( menuButton.IsPressed() );
}

bool OptionsMenu::DoInvertControls() const
{
	return( invertControls.IsChecked() );
}

bool OptionsMenu::DoClickMovement() const
{
	return( clickMovement.IsChecked() );
}
