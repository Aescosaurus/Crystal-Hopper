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
	constexpr Vec2_( T val ) = delete;
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
	template<typename U>
	constexpr U GetLengthSq() const
	{
		return( U( x ) * U( x ) + U( y ) * U( y ) );
	}
	template<typename U>
	constexpr U GetLength() const
	{
		return( U( sqrt( GetLengthSq<U>() ) ) );
	}
	constexpr Vec2_<T> GetNormalized() const
	{
		const auto len = GetLength<T>();
		return( Vec2_<T>{ *this } / len );
	}
	template<typename U>
	U GetAngle() const
	{
		return( atan2( U( y ),U( x ) ) );
	}
	static T Dot( const Vec2_<T>& first,const Vec2_<T>& second )
	{
		return( first.x * second.x +
			first.y * second.y );
	}
	Vec2_<T> GetPerp() const
	{
		return( Vec2_<T>{ y,-x } );
	}
	Vec2_<T> X() const
	{
		return( Vec2_<T>{ x,0.0f } );
	}
	Vec2_<T> Y() const
	{
		return( Vec2_<T>{ 0.0f,y } );
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