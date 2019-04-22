#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>
#include "Graphics.h"
#include "ChiliUtils.h"
#include <algorithm>

Surface::Surface( int width,int height ) :
	width( width ),
	height( height ),
	pixels( width * height )
{}

Surface::Surface( const std::string& filename )
{
	std::ifstream file( filename,std::ios::binary );
	assert( file );

	BITMAPFILEHEADER bmFileHeader;
	file.read( reinterpret_cast< char* >( &bmFileHeader ),
		sizeof( bmFileHeader ) );

	BITMAPINFOHEADER bmInfoHeader;
	file.read( reinterpret_cast< char* >( &bmInfoHeader ),
		sizeof( bmInfoHeader ) );

	assert( bmInfoHeader.biBitCount == 24 ||
		bmInfoHeader.biBitCount == 32 );
	assert( bmInfoHeader.biCompression == BI_RGB );

	const bool is32b = bmInfoHeader.biBitCount == 32;

	width = bmInfoHeader.biWidth;

	// Test for reverse row order and
	//  control y loop accordingly.
	int yStart;
	int yEnd;
	int dy;
	if( bmInfoHeader.biHeight < 0 )
	{
		height = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bmInfoHeader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}

	pixels.resize( width * height );

	file.seekg( bmFileHeader.bfOffBits );
	// Padding is for 24 bit depth only.
	const int padding = ( 4 - ( width * 3 ) % 4 ) % 4;

	for( int y = yStart; y != yEnd; y += dy )
	{
		for( int x = 0; x < width; ++x )
		{
			PutPixel( x,y,Color( file.get(),file.get(),file.get() ) );
			if( is32b )
			{
				file.seekg( 1,std::ios::cur );
			}
		}
		if( !is32b )
		{
			file.seekg( padding,std::ios::cur );
		}
	}

	*this = this->GetExpandedBy( Vei2{ 4,4 } );
}

Surface::Surface( const Surface& other,const RectI& clip )
{
	*this = other.GetClipped( clip );
}

Surface::Surface( const Surface& other,const Vei2& expandSize )
{
	*this = other.GetExpandedBy( expandSize );
}

Surface::Surface( const Surface& other,bool xFlipped,bool yFlipped )
{
	Surface guineaPig = { other.GetWidth(),other.GetHeight() };

	if( xFlipped ) guineaPig = other.GetXReversed();

	if( yFlipped ) guineaPig = guineaPig.GetYReversed();

	*this = guineaPig;
}

Surface::Surface( Surface&& donor )
{
	*this = std::move( donor );
}

Surface& Surface::operator=( Surface&& rhs )
{
	width = rhs.width;
	height = rhs.height;
	pixels = std::move( rhs.pixels );

	rhs.width = 0;
	rhs.height = 0;

	return( *this );
}

void Surface::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	pixels.data()[y * width + x] = c;
}

void Surface::PutPixelApprox( float x,float y,Color c )
{
	assert( x >= 0.0f );
	assert( y >= 0.0f );
	assert( x < float( width ) );
	assert( y < float( height ) );

	const auto xData = x - floor( x );
	const auto yData = y - floor( y );

	const auto x1 = int( floor( x ) );
	const auto x2 = int( ceil( x ) );
	const auto y1 = int( floor( y ) );
	const auto y2 = int( ceil( y ) );

	PutPixel( x1,y1,c );
	PutPixel( x2,y1,c );
	PutPixel( x1,y2,c );
	PutPixel( x2,y2,c );
}

void Surface::PutPixelApproxSafe( float x,float y,Color c )
{
	const auto xData = x - floor( x );
	const auto yData = y - floor( y );

	auto x1 = int( floor( x ) );
	auto x2 = int( ceil( x ) );
	auto y1 = int( floor( y ) );
	auto y2 = int( ceil( y ) );

	x1 = std::max( 0,std::min( width - 1,x1 ) );
	x2 = std::max( 0,std::min( width - 1,x2 ) );
	y1 = std::max( 0,std::min( height - 1,y1 ) );
	y2 = std::max( 0,std::min( height - 1,y2 ) );

	PutPixel( x1,y1,c );
	PutPixel( x2,y1,c );
	PutPixel( x1,y2,c );
	PutPixel( x2,y2,c );
}

void Surface::DrawRect( int x,int y,int width,int height,Color c )
{
	for( int i = y; i < y + height; ++i )
	{
		for( int j = x; j < x + width; ++j )
		{
			PutPixel( j,i,c );
		}
	}
}

Color Surface::GetPixel( int x,int y ) const
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	return pixels.data()[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

Vei2 Surface::GetSize() const
{
	return Vei2{ width,height };
}

RectI Surface::GetRect() const
{
	return{ 0,width,0,height };
}

Surface Surface::GetExpandedBy( const Vei2& amount ) const
{
	Surface bigger = { amount.x * GetWidth(),amount.y * GetHeight() };

	for( int y = 0; y < this->height; ++y )
	{
		for( int x = 0; x < this->width; ++x )
		{
			bigger.DrawRect( x * amount.x,y * amount.y,
				int( amount.x ),int( amount.y ),
				GetPixel( x,y ) );
		}
	}

	return( bigger );
}

Surface Surface::GetXReversed() const
{
	Surface flipped = Surface{ width,height };

	for( int y = 0; y < height; ++y )
	{
		int otherX = 0;
		// Loop in reverse x.
		for( int x = width - 1; x >= 0; --x )
		{
			flipped.PutPixel( otherX,y,GetPixel( x,y ) );
			++otherX;
		}
	}

	return( flipped );
}

Surface Surface::GetYReversed() const
{
	Surface flipped = Surface{ width,height };

	int otherY = 0;
	// Loop in reverse y.
	for( int y = height - 1; y >= 0; --y )
	{
		for( int x = width - 1; x >= 0; --x )
		{
			flipped.PutPixel( x,otherY,GetPixel( x,y ) );
		}
		++otherY;
	}

	return( flipped );
}

Surface Surface::GetClipped( const RectI& clip ) const
{
	Surface clipped = { clip.GetWidth(),clip.GetHeight() };

	int i = 0;
	int j = 0;
	for( int y = clip.top; y < clip.bottom; ++y )
	{
		for( int x = clip.left; x < clip.right; ++x )
		{
			clipped.PutPixel( j,i,GetPixel( x,y ) );
			++j;
		}
		j = 0;
		++i;
	}

	return( clipped );
}

Surface Surface::GetRotated( float angle ) const
{
	Matrix rotMat = Matrix::Rotation( angle );
	// const auto longest = float( std::max( width,height ) );
	// const int rotWidth = longest * cos( angle ) + longest * sin( angle );
	// const int rotHeight = rotWidth;
	int rotWidth;
	int rotHeight;

	if( angle < chili::pi / 2.0f )
	{
		rotWidth = int( ( float( width ) * cos( angle ) ) +
			( float( height ) * sin( angle ) ) );
		rotHeight = int( ( float( width ) * sin( angle ) ) +
			( float( height ) * cos( angle ) ) );
	}
	else if( angle < chili::pi )
	{
		// rotated angle theta = p - 90
	
		rotWidth = int( ( float( height ) * cos( angle ) ) +
			( float( width ) * sin( angle ) ) );
		rotHeight = int( ( float( height ) * sin( angle ) ) +
			( float( width ) * cos( angle ) ) );
	}
	else
	{
		assert( false );
	}

	Surface rotated{ rotWidth + 2,rotHeight + 2 };

	// Fill background with chroma'd pixels.
	rotated.DrawRect( 0,0,rotated.width,rotated.height,
		Colors::Magenta );

	const auto center = Vec2( GetSize() ) / 2.0f;
	const auto rotatedCenter = Vec2( rotated.GetSize() ) / 2.0f;
	const auto centerAdd = rotatedCenter - center;

	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			// From Graphics::DrawSprite:
			// --------------------------
			// const Vei2 center = { x + s.GetWidth() / 2,y + s.GetHeight() / 2 };
			// auto drawPos = Vec2( Vei2{ x + sx - srcRect.left,
			// 	y + sy - srcRect.top } );
			// drawPos -= Vec2( center );
			// drawPos = rotationMatrixrix * Vec2( drawPos );
			// drawPos += Vec2( center );
			// effect(
			// 	// Mirror in x.
			// 	s.GetPixel( xOffset - sx,sy ),
			// 	drawPos.x,
			// 	drawPos.y,
			// 	*this
			// );
			// --------------------------

			Vec2 drawPos = { float( x ),float( y ) };
			drawPos -= center;
			drawPos = rotMat * drawPos;
			drawPos += center;

			rotated.PutPixelApprox( drawPos.x + centerAdd.x,
				drawPos.y + centerAdd.y,
				GetPixel( x,y ) );

			auto bop = 1.1f;
		}
	}

	return( rotated );
}
