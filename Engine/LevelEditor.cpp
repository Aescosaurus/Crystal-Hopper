#include "LevelEditor.h"
#include <fstream>
#include "SpriteEffect.h"

LevelEditor::LevelEditor( Keyboard& kbd,Mouse& mouse,Graphics& gfx )
	:
	kbd( kbd ),
	mouse( mouse ),
	gfx( gfx )
{}

void LevelEditor::Update()
{
	while( !mouse.IsEmpty() )
	{
		const auto e = mouse.Read();
		switch( e.GetType() )
		{
		case Mouse::Event::Type::LPress:
			if( canClick )
			{
				platforms.emplace_back( std::pair<Vei2,float>{
					mouse.GetPos(),curRotation } );
			}
			canClick = false;
			break;
		case Mouse::Event::Type::LRelease:
			canClick = true;
			break;
		case Mouse::Event::Type::WheelUp:
			curRotation -= rotationSpeed;
			break;
		case Mouse::Event::Type::WheelDown:
			curRotation += rotationSpeed;
			break;
		}
	}
}

void LevelEditor::Draw() const
{
	const auto chroma = SpriteEffect::SafeChroma{ Colors::Magenta };

	for( const auto& plat : platforms )
	{
		DrawSpriteCentered( plat.first,*platformSpr,
			chroma,Matrix::Rotation( plat.second ) );
	}

	DrawSpriteCentered( mouse.GetPos(),*platformSpr,chroma,
		Matrix::Rotation( curRotation ) );
}

void LevelEditor::WriteToFile()
{
	std::ofstream out{ outFilePath };

	out << "Level Title\n"; // Level title.
	out << "1\n25\n50\n75\n90\n"; // Star weights.

	// Floor data.
}