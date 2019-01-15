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
	if( save.Update( mouse.GetPos(),mouse.LeftIsPressed() ) )
	{
		WriteToFile();
	}

	while( !mouse.IsEmpty() )
	{
		const auto e = mouse.Read();
		switch( e.GetType() )
		{
		case Mouse::Event::Type::LPress:
			if( canClick && !save.IsHovering() )
			{
				entities[int( brush )].emplace_back( std::pair<Vei2,float>{
					mouse.GetPos(),curRotation } );
			}
			canClick = false;
			break;
		case Mouse::Event::Type::LRelease:
			canClick = true;
			break;
		case Mouse::Event::Type::WheelUp:
			if( kbd.KeyIsPressed( VK_CONTROL ) )
			{
				IncrementBrush();
			}
			else
			{
				curRotation -= rotationSpeed;
			}
			break;
		case Mouse::Event::Type::WheelDown:
			if( kbd.KeyIsPressed( VK_CONTROL ) )
			{
				DecrementBrush();
			}
			else
			{
				curRotation += rotationSpeed;
			}
			break;
		}
	}
}

void LevelEditor::Draw() const
{
#if NDEBUG
	gfx.DrawSprite( 0,0,*earthBG,SpriteEffect::Copy{} );
#endif

	const auto chroma = SpriteEffect::SafeChroma{ Colors::Magenta };

	for( int i = 0; i < int( Entity::Count ); ++i )
	{
		for( const auto& item : entities[i] )
		{
			DrawSpriteCentered( item.first,surfs[i],
				chroma,i == int( Entity::Platform ) ||
				i == int( Entity::MovingPlatform )
				? Matrix::Rotation( item.second )
				: Matrix::Rotation( 0.0f ) );
		}
	}

	if( !save.IsHovering() )
	{
		DrawSpriteCentered( mouse.GetPos(),
			surfs[int( brush )],chroma,
			Matrix::Rotation( curRotation ) );
	}

	save.Draw( gfx );
}

void LevelEditor::Reset()
{
	for( int i = 0; i < int( Entity::Count ); ++i )
	{
		entities[i].clear();
	}
	canClick = false;
	curRotation = 0.0f;
}

void LevelEditor::WriteToFile()
{
	std::string out = "";

	out += "Level Title\n"; // Level title.
	out += "-1\n"; // Jump limit.
	out += "1\n2\n3\n4\n5\n"; // Star weights.

	// Entities data.
	for( const auto& item : entities[int( Entity::Platform )] )
	{
		out += "Floor|";
		out += std::to_string( item.first.x ) + '|';
		out += std::to_string( item.first.y ) + '|';
		out += std::to_string( item.second ) + '\n';
	}
	for( const auto& item : entities[int( Entity::Crystal )] )
	{
		out += "Crystal|";
		out += std::to_string( item.first.x ) + '|';
		out += std::to_string( item.first.y ) + '\n';
	}
	for( const auto& item : entities[int( Entity::SpikyBoi )] )
	{
		out += "SpikyBoi|";
		out += std::to_string( item.first.x ) + '|';
		out += std::to_string( item.first.y ) + '\n';
	}
	for( const auto& item : entities[int( Entity::MovingPlatform )] )
	{
		out += "MovingFloor|";
		out += std::to_string( item.first.x ) + '|';
		out += std::to_string( item.first.y ) + '|';
		out += std::to_string( item.second ) + '|';
		out += std::to_string( item.first.x - 50 ) + '|';
		out += std::to_string( item.first.x + 50 ) + '|';
		out += "100\n";
	}

	out.pop_back(); // Remove the last newline.

	std::ofstream fileOutStream{ outFilePath };
	fileOutStream << out;
}

void LevelEditor::IncrementBrush()
{
	brush = Entity( int( brush ) + 1 );
	if( brush == Entity::Count )
	{
		brush = Entity::Platform;
	}
}

void LevelEditor::DecrementBrush()
{
	brush = Entity( int( brush ) - 1 );
	if( int( brush ) == int( Entity::Platform ) - 1 )
	{
		brush = Entity( int( Entity::Count ) - 1 );
	}
}
