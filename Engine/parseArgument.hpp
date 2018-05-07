#pragma once
#include <string>
#include "hresult.hpp"

namespace MicroScript
{
	template<class tArg>
	inline HRESULT parseArgument( const char* arg, size_t length, tArg& result );

	template<>
	inline HRESULT parseArgument<bool>( const char* arg, size_t length, bool& result )
	{
		if( 0 == _strnicmp( arg, "true", length ) )
		{
			result = true;
			return S_OK;
		}
		if( 0 == _strnicmp( arg, "false", length ) )
		{
			result = false;
			return S_OK;
		}
		return E_INVALIDARG;
	}

	template<>
	inline HRESULT parseArgument<int32_t>( const char* arg, size_t length, int32_t& result )
	{
		char *temp;
		result = strtol( arg, &temp, 0 );
		if( temp == arg || temp != arg + length || ( ( result == LONG_MIN || result == LONG_MAX ) && errno == ERANGE ) )
			return E_INVALIDARG;
		return S_OK;
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
	inline HRESULT parseArgument<std::string>( const char* arg, size_t length, std::string& result )
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