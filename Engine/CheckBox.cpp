#include "CheckBox.h"
#include "SpriteEffect.h"

CheckBox::CheckBox( const Vei2& center,const std::string& text )
	:
	size( GetSize( text ) ),
	pos( center ),
	text( text )
{}

bool CheckBox::Update( const Vei2& mousePos,bool mouseDown )
{
	hovering = ( ContainsPoint( mousePos ) );

	if( mouseDown && hovering && canClick )
	{
		checked = !checked;
	}

	if( !mouseDown ) canClick = true;
	else canClick = false;

	return( IsChecked() );
}

void CheckBox::Draw( Graphics& gfx ) const
{
	const auto drawCol = hovering ? Colors::White : Colors::LightGray;

	gfx.DrawSpriteNormal( pos.x,pos.y + padding.y / 2,
		*( IsChecked() ? full : empty ),
		SpriteEffect::Substitution{ Colors::Magenta,drawCol } );
	luckyPixel->DrawText( text,pos + Vei2{ padding.x * 3,padding.y / 2 },
		drawCol,gfx );
}

void CheckBox::Read( const std::string& line )
{
	std::string val = "";
	bool writingVal = false;
	for( char c : line )
	{
		if( c == ':' ) writingVal = true;
		else if( writingVal && c != ' ' ) val += c;
	}
	checked = ( val == "ON" );
}

std::string CheckBox::Write() const
{
	return( text + ": " + ( checked ? "ON" : "OFF" ) );
}

bool CheckBox::IsChecked() const
{
	return( checked );
}

Vei2 CheckBox::GetSize( const std::string& msg ) const
{
	const int msgWidth = int( msg.size() );
	const auto fontCharSize = luckyPixel->GetCharSize();
	return( Vei2{ fontCharSize.x * msgWidth + full->GetWidth(),
		fontCharSize.y } + padding );
}

bool CheckBox::ContainsPoint( const Vei2& point ) const
{
	return( point.x > pos.x && point.x < pos.x + size.x &&
		point.y > pos.y && point.y < pos.y + size.y );
}
