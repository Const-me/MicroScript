#pragma once
#include <string>
#include "ParserBase.hpp"

namespace MicroScript
{
	// Parse and interpret the complete script.
	class ScriptParser: public ParserBase
	{
	public:
		ScriptParser( const std::string& str ) :
			ParserBase( str.c_str(), str.length() ) { }

		ScriptParser( const char* begin, size_t length ) :
			ParserBase( begin, length ) {}

		HRESULT interpret();
	};
}