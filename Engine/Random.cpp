#include "Random.h"

std::mt19937 Random::rng{ std::random_device{}() };

Random::Random( int min,int max )
{
	std::uniform_int_distribution<int> dist( min,max );
	val = float( dist( rng ) );
}

Random::Random( float min,float max )
{
	if( min > max ) std::swap( min,max );
	std::uniform_real_distribution<float> dist( min,max );
	val = dist( rng );
}

Random::operator int() const
{
	return( int( val ) );
}

Random::operator float() const
{
	return( val );
}
