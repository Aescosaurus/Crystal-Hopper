#include "MarsTurret.h"

MarsTurret::MarsTurret( const Vec2& pos,float angle )
	:
	pos( pos ),
	rotMat( Matrix::Rotation( angle ) ),
	baseAnim( 0,0,64,64,5,*pSurfSheet,0.2f ),
	topAnim( 0,64,64,64,5,*pSurfSheet,0.2f )
{}

void MarsTurret::Update( const Vec2& playerPos,float dt )
{
}

void MarsTurret::Draw( Graphics& gfx ) const
{

}

Circle MarsTurret::GetColl() const
{
	return( Circle{ pos,float( radius ) } );
}
