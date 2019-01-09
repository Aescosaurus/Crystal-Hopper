#include "SpikyBoi.h"

SpikyBoi::SpikyBoi( const Vei2& pos )
	:
	pos( pos )
{}

void SpikyBoi::Update( float dt )
{
}

void SpikyBoi::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( Vei2( pos ),radius,Colors::Red );
}

Circle SpikyBoi::GetCollider() const
{
	return( Circle{ pos,float( radius ) } );
}
