#pragma once

#include "Vec2.h"
#include <string>
#include "Graphics.h"
#include "Codex.h"

class PlanetMenu
{
public:
	PlanetMenu( const Vei2& pos,const std::string& img );

	void Update( const Vei2& mousePos );
	void Draw( const Vei2& offset,Graphics& gfx ) const;
private:
	Vei2 pos;
	CSurfPtr img;
};