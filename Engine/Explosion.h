#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Animation.h"
#include "Codex.h"

class Explosion
{
public:
	enum class Type
	{
		Explosion = 0,
		Confetti,
		CrystalDissolve,
		Count
	};
public:
	Explosion( const Vec2& pos,Type t );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	bool Done() const;
private:
	static constexpr Vei2 size = { 32,32 };
	Vei2 pos;
	// CSurfPtr surfSheet = SurfCodex::Fetch( "Images/ExplodeAnim.bmp" );
	static CSurfPtr surfSheets[int( Type::Count )];
	// static constexpr char* sources[int( Type::Count )]
	// {
	// 	"Images/ExplodeAnim.bmp",
	// 	"Images/ConfettiAnim.bmp"
	// };
	Animation fadeAway;
	bool willDestroy = false;
};