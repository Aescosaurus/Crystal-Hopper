#include "Crystal.h"

Crystal::Crystal( const Vec2& pos )
	:
	pos( pos )
{}

void Crystal::Draw( Graphics& gfx ) const
{
	if( !collected )
	{
		gfx.DrawCircle( Vei2( pos ),radius,Colors::Cyan );
	}
}

void Crystal::Collect()
{
	collected = true;
}

Circle Crystal::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}

bool Crystal::WillRemove() const
{
	return( collected );
}
