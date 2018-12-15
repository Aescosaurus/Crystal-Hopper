#pragma once

template<typename T>
class Vec2_
{
public:
	constexpr Vec2_()
	{
		*this = Fake();
	}
	constexpr Vec2_( T x,T y )
		:
		x( x ),
		y( y )
	{}
	template<typename U>
	constexpr operator Vec2_<U>() const
	{
		return( Vec2_<U>{ U( x ),U( y ) } );
	}
	constexpr Vec2_<T>& operator+=( const Vec2_<T>& rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return( *this );
	}
	constexpr Vec2_<T> operator+( const Vec2_<T>& rhs ) const
	{
		auto temp = *this;
		temp += rhs;
		return( temp );
	}
	constexpr Vec2_<T>& operator-=( const Vec2_<T>& rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return( *this );
	}
	constexpr Vec2_<T> operator-( const Vec2_<T>& rhs ) const
	{
		auto temp = *this;
		temp -= rhs;
		return( temp );
	}
	constexpr Vec2_<T>& operator*=( T amount )
	{
		x *= amount;
		y *= amount;
		return( *this );
	}
	constexpr Vec2_<T> operator*( T amount ) const
	{
		auto temp = *this;
		temp *= amount;
		return( temp );
	}
	constexpr Vec2_<T>& operator/=( T amount )
	{
		x /= amount;
		y /= amount;
		return( *this );
	}
	constexpr Vec2_<T> operator/( T amount ) const
	{
		auto temp = *this;
		temp /= amount;
		return( temp );
	}
	constexpr bool operator==( const Vec2_<T>& rhs ) const
	{
		return( x == rhs.x && y == rhs.y );
	}
	constexpr bool operator!=( const Vec2_<T>& rhs ) const
	{
		return( !( *this == rhs ) );
	}
	constexpr Vec2_<T> operator-() const
	{
		return( Vec2_<T>{ -x,-y } );
	}
	constexpr T GetLengthSq() const
	{
		return( x * x + y * y );
	}
	constexpr T GetLength() const
	{
		return( sqrt( GetLengthSq() ) );
	}
	constexpr Vec2_<T> GetNormalized() const
	{
		const auto len = GetLength();
		return( Vec2_<T>{ *this } / len );
	}
	float GetAngle() const
	{
		return( atan2( float( y ),float( x ) ) );
	}
	static constexpr Vec2_<T> Fake()
	{
		return( Vec2_<T>{ T( -9999 ),T( -9999 ) } );
	}
public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;