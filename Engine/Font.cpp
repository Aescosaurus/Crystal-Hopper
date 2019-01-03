#include "Font.h"
#include <cassert>
#include "SpriteEffect.h"

Font::Font( const std::string& filename,Color chroma )
	:
	surf( Surface{ filename,Vei2{ 4,4 } } ),
	// calculate glyph dimensions from bitmap dimensions
	glyphWidth( surf.GetWidth() / nColumns ),
	glyphHeight( surf.GetHeight() / nRows ),
	chroma( chroma )
{
	// verify that bitmap had valid dimensions
	assert( glyphWidth * nColumns == surf.GetWidth() );
	assert( glyphHeight * nRows == surf.GetHeight() );
}

void Font::DrawText( const std::string& text,const Vei2& pos,Color color,Graphics& gfx ) const
{
	DrawText( text,pos,color,
		SpriteEffect::Substitution{ chroma,color },
		gfx );
}

Vei2 Font::GetCharSize() const
{
	return Vei2{ glyphWidth,glyphHeight };
}

RectI Font::MapGlyphRect( char c ) const
{
	assert( c >= firstChar && c <= lastChar );
	// font sheet glyphs start at ' ', calculate index into sheet
	const int glyphIndex = c - ' ';
	// map 1d glyphIndex to 2D coordinates
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;
	// convert the sheet grid coords to pixel coords in sheet
	return RectI(
		{ xGlyph * glyphWidth,yGlyph * glyphHeight },
		glyphWidth,glyphHeight
	);
}