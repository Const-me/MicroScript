#pragma once
#include <errno.h>
#include <limits>
#ifdef _WIN32
#include <string.h>
#else
#include <strings.h>
#endif

namespace MicroScript
{
	inline bool compareString( const char* a, const std::string& b, size_t length )
	{
		if( b.length() != length )
			return false;
#ifdef _WIN32
		return 0 == _strnicmp( a, b.c_str(), length );
#else
		return 0 == strncasecmp( a, b.c_str(), length );
#endif
	}

	inline bool parseInt( const char* arg, size_t length, int32_t& result )
	{
		char *temp;
		result = strtol( arg, &temp, 0 );
		if( temp == arg || temp != arg + length )
			return false;
		using lim = std::numeric_limits<int32_t>;
		if( ( result == lim::min() || result == lim::max() ) && errno == ERANGE )
			return false;
		return true;
	}
}