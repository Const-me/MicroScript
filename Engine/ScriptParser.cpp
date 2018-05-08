#include "stdafx.h"
#include "ScriptParser.h"
#include "Registrator.h"
using namespace MicroScript;

#define CHECK_OK( expr ) { const HRESULT __hr = ( expr ); if( FAILED( __hr ) ) return S_OK; }

namespace
{
	inline bool notEmpty( char c )
	{
		switch( c )
		{
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			return false;
		}
		return true;
	}
}

HRESULT ScriptParser::interpret()
{
	while( true )
	{
		CHECK_OK( advance( notEmpty ) );

		const char* const name = m_next;
		CHECK( advanceTo( '(' ) );
		const char* nameEndLast = m_next - 1;
		while( nameEndLast > name && isWhitespace( *nameEndLast ) )
			nameEndLast--;
		if( nameEndLast <= name )
			return E_INVALIDARG;

		const iFunction* func = resolveFunction( std::string{ name, nameEndLast + 1 } );
		if( nullptr == func )
			return DISP_E_UNKNOWNNAME;

		CHECK( advanceTo( '(' ) );
		const char* const arglistBegin = m_next;
		const size_t length = m_end - arglistBegin;
		CHECK( func->invoke( arglistBegin, length ) );

		while( true )
		{
			CHECK( advanceTo( ')' ) );
			if( m_next[ -1 ] == '\\' )
			{
				m_next++;
				continue;
			}
			m_next++;
			break;
		}
	}
}