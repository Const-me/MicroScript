#pragma once
#include "ParserBase.hpp"

namespace MicroScript
{
	// Utility class to parse argument list strings like ( 0, true, "string" ) into a sequence of string values
	class ArgumentsParser: public ParserBase
	{
	public:
		ArgumentsParser( const char* begin, size_t length ) :
			ParserBase( begin, length ) {}

		HRESULT start();
		HRESULT next( const char** begin, size_t &length );
		HRESULT finish();

	private:
		static HRESULT skipTrailingSpaces( const char** begin, size_t &length );
	};
}