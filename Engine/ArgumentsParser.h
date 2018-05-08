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

		// Start parsing, advance to the first character after '('
		HRESULT start();

		// Extract an argument
		HRESULT next( const char** begin, size_t &length );

		// Finish parsing, advance to the ')'
		HRESULT finish();

	private:
		static HRESULT skipTrailingSpaces( const char** begin, size_t &length );
	};
}