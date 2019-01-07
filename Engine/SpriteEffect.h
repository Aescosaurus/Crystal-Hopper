#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma( Color c )
			:
			chroma( c )
		{}
		void operator()( Color cSrc,float xDest,float yDest,Graphics& gfx ) const
		{
			if( cSrc != chroma )
			{
				gfx.PutPixelApprox( xDest,yDest,cSrc );
			}
		}
	private:
		Color chroma;
	};
	class Substitution
	{
	public:
		Substitution( Color c,Color s )
			:
			chroma( c ),
			sub( s )
		{}
		void operator()( Color cSrc,float xDest,float yDest,Graphics& gfx ) const
		{
			if( cSrc != chroma )
			{
				gfx.PutPixelApprox( xDest,yDest,sub );
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
	class Copy
	{
	public:
		void operator()( Color cSrc,float xDest,float yDest,Graphics& gfx )
		{
			gfx.PutPixelApprox( xDest,yDest,cSrc );
		}
	};
	class Ghost
	{
	public:
		Ghost( Color c )
			:
			chroma( c )
		{}
		void operator()( Color src,float xDest,float yDest,Graphics& gfx ) const
		{
			if( src != chroma )
			{
				const Color dest = gfx.GetPixel( int( xDest ),int( yDest ) );
				const Color blend =
				{
					unsigned char( ( src.GetR() + dest.GetR() ) / 2 ),
					unsigned char( ( src.GetG() + dest.GetG() ) / 2 ),
					unsigned char( ( src.GetB() + dest.GetB() ) / 2 )
				};
			}
		}
	private:
		Color chroma;
	};
	class Fade
	{
	public:
		Fade( Color chroma,float opacity )
			:
			chroma( chroma ),
			opacity( opacity )
		{
			assert( opacity >= 0.0f && opacity <= 1.0f );
		}
		void operator()( Color cSrc,float xDest,float yDest,Graphics& gfx )
		{
			if( cSrc != chroma )
			{
				gfx.PutPixelAlpha( int( xDest ),int( yDest ),cSrc,opacity );
			}
		}
	private:
		Color chroma;
		float opacity;
	};
	// Dissolves image by scanline and blends drawn pixels with a color,
	//  good for dying enemies I guess.
	class DissolveHalfTint
	{
	public:
		DissolveHalfTint( Color chroma,Color tint,float percent )
			:
			chroma( chroma ),
			// divide channels by 2 via shift, mask to prevent bleeding between channels
			tint_pre( ( tint.dword >> 1u ) & 0b01111111011111110111111101111111u ),
			filled( int( float( height ) * percent ) )
		{}
		void operator()( Color src,float xDest,float yDest,Graphics& gfx ) const
		{
			// height mask determines frequency of vertical dissolve sections
			if( src != chroma && ( int( yDest ) & height_mask ) < filled )
			{
				const Color blend = tint_pre.dword +
					// divide channels by 2 via shift, mask to prevent bleeding between channels
					( ( src.dword >> 1u ) & 0b01111111011111110111111101111111u );
				gfx.PutPixelApprox( xDest,yDest,blend );
			}
		}
	private:
		Color chroma;
		Color tint_pre;
		static constexpr int height = 4;
		static constexpr int height_mask = height - 1;
		int filled;
	};
	class SubstituteFade
	{
	public:
		SubstituteFade( Color chroma,Color sub,float fadeAmount )
			:
			chroma( chroma ),
			substitution( sub ),
			fadeAmount( fadeAmount )
		{}
		void operator()( Color cSrc,float xDest,float yDest,Graphics& gfx )
		{
			if( cSrc != chroma )
			{
				gfx.PutPixelApprox( xDest,yDest,cSrc );
				gfx.PutPixelAlpha( int( xDest ),int( yDest ),substitution,fadeAmount );
			}
		}
	private:
		Color chroma;
		Color substitution;
		float fadeAmount;
	};
	class SafeChroma
	{
	public:
		SafeChroma( Color c )
			:
			chroma( c )
		{}
		void operator()( Color cSrc,float xDest,float yDest,Graphics& gfx ) const
		{
			if( cSrc != chroma )
			{
				gfx.PutPixelSafeApprox( xDest,yDest,cSrc );
			}
		}
	private:
		Color chroma;
	};
}
