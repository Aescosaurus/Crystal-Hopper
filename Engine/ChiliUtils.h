#pragma once

namespace chili
{
	static constexpr float pi = 3.141592653f;
	static constexpr float deg2rad( float deg )
	{
		return( deg * ( pi / 180.0f ) );
	}
}