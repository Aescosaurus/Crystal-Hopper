#include "Button.h"
#include "SpriteEffect.h"

Button::Button( const Vei2& center,const std::string& text )
	:
	size( GetSize( text ) ),
	pos( center - size / 2 ),
	text( text ),
	bg( size.x + edgeSpr->GetWidth() * 3,size.y ),
	lit( size.x + edgeSpr->GetWidth() * 3,size.y )
{
	bg.DrawRect( 0,0,bg.GetWidth(),bg.GetHeight(),Colors::Magenta );
	lit.DrawRect( 0,0,bg.GetWidth(),bg.GetHeight(),Colors::Magenta );

	Vei2 sprPos = Vei2::Zero();
	bg.Overlay( *edgeSpr,sprPos );
	lit.Overlay( *edgeLit,sprPos );
	sprPos.x += edgeSpr->GetWidth();
	for( int i = 0; i < text.size(); ++i )
	{
		bg.Overlay( *mainSpr,sprPos );
		lit.Overlay( *mainLit,sprPos );
		sprPos.x += luckyPixel->GetCharSize().x;
	}
	bg.Overlay( edgeSpr->GetXReversed(),sprPos );
	lit.Overlay( edgeLit->GetXReversed(),sprPos );
}

bool Button::Update( const Vei2& mousePos,bool mouseDown )
{
	hovering = ( ContainsPoint( mousePos ) );

	if( mouseDown && hovering && canClick )
	{
		clicking = true;
	}
	else clicking = false;

	if( !mouseDown ) canClick = true;
	else canClick = false;

	return( clicking );
}

void Button::Draw( Graphics& gfx ) const
{
	gfx.DrawSpriteNormal( pos.x/* - edgeSpr->GetWidth()*/,pos.y,
		hovering ? lit : bg,SpriteEffect::Chroma{} );

	const auto drawCol = hovering
		? Colors::White
		: Colors::LightGray;

	luckyPixel->DrawText( text,pos + padding / 2,
		drawCol,gfx );
}

void Button::DrawBackground( Graphics& gfx ) const
{
	const auto drawCol = hovering
		? Colors::White
		: Colors::LightGray;
	gfx.DrawRect( pos.x,pos.y,size.x,size.y,
		hovering ? Colors::LightGray : Colors::DarkGray );

	luckyPixel->DrawText( text,pos + padding / 2,
		drawCol,gfx );
}

void Button::Reset()
{
	hovering = false;
	canClick = false;
	clicking = false;
}

bool Button::IsPressed() const
{
	return( clicking );
}

bool Button::IsHovering() const
{
	return( hovering );
}

Vei2 Button::GetSize( const std::string& msg ) const
{
	const int msgWidth = int( msg.size() );
	const auto fontCharSize = luckyPixel->GetCharSize();
	return( Vei2{ fontCharSize.x * msgWidth,
		fontCharSize.y } + padding );
}

bool Button::ContainsPoint( const Vei2& point ) const
{
	return( point.x > pos.x && point.x < pos.x + size.x + edgeSpr->GetWidth() &&
		point.y > pos.y && point.y < pos.y + size.y + 4 );
}
