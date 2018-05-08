#include "stdafx.h"
#include "Engine/Registrator.h"
#include "Engine/ScriptParser.h"

namespace MicroScript
{
	// Register a couple of functions
	HRESULT helloWorld()
	{
		printf( "Hello, World.\n" );
		return S_OK;
	}
	HRESULT print( std::string str )
	{
		printf( "%s\n", str.c_str() );
		return S_OK;
	}
	HRESULT multiply( int a, int b )
	{
		printf( "%i * %i = %i\n", a, b, a * b );
		return S_OK;
	}
	REGISTER_SCRIPT_FUNC( helloWorld );
	REGISTER_SCRIPT_FUNC( print );
	REGISTER_SCRIPT_FUNC( multiply );

	// This won't compile because the engine doesn't specialize parseArgument<> for doubles:
	// HRESULT unsupported( double x ) { return E_FAIL; }
	// REGISTER_SCRIPT_FUNC( unsupported );
}

int main()
{
	using namespace std::literals;
	// Script source. Following characters need to be escaped in the strings: "," => "\,", ")" => "\)", and optionally "\" => "\\"
	// The parser is very basic, that's not how people normally parse script languages. The focus of this demo is interpreter, not parser.
	// Haven't tested but should probably work with UTF8, too.
	const std::string src = R"fffuuu(

helloWorld()

print( "Hi\, this is from MicroScript :-\)" )

multiply( 2, 2 )

)fffuuu"s;

	// Run the script
	MicroScript::ScriptParser parser{ src };
	const auto hr = parser.interpret();

	printf( "\nStatus code %08x\n", hr );
	return 0;
}