#include "stdafx.h"
#include <string>
#include "utils.hpp"
#include "parseArgument.h"

namespace MicroScript
{
	template<>
	HRESULT parseArgument<bool>( const char* arg, size_t length, bool& result )
	{
		using namespace std::literals;
		if( compareString( arg, "true"s, length ) )
		{
			result = true;
			return S_OK;
		}
		if( compareString( arg, "false"s, length ) )
		{
			result = false;
			return S_OK;
		}
		return E_INVALIDARG;
	}

	template<>
	HRESULT parseArgument<int32_t>( const char* arg, size_t length, int32_t& result )
	{
		return parseInt( arg, length, result ) ? S_OK : E_INVALIDARG;
	}

	// C++/17 still can't replace substrings. Even Visual Basic 6.0 had a built-in Replace function, back in 2000 :-(
	inline void replace( std::string& str, const std::string& from, const std::string& to )
	{
		// http://stackoverflow.com/a/3418285/126995
		if( from.empty() )
			return;
		size_t start_pos = 0;
		while( ( start_pos = str.find( from, start_pos ) ) != std::string::npos )
		{
			str.replace( start_pos, from.length(), to );
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}

	template<>
	HRESULT parseArgument<std::string>( const char* arg, size_t length, std::string& result )
	{
		result = std::string{ arg, arg + length };
		using namespace std::literals;
		// Handle escape sequences in strings, "\,", "\)", "\\"
		replace( result, "\\,"s, ","s );
		replace( result, "\\)"s, ")"s );
		replace( result, "\\\\"s, "\\"s );
		if( result.length() >= 2 )
		{
			if( result[ 0 ] == '\"' && result[ result.length() - 1 ] == '\"' )
				result = result.substr( 1, result.length() - 2 );
		}
		return S_OK;
	}
}