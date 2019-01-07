#pragma once

#include <random>

class Random
{
public:
	Random( int min,int max );
	Random( float min,float max );

	operator int() const;
	operator float() const;
private:
	static std::mt19937 rng;
	float val;
};