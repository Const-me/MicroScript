#include "stdafx.h"
#include "ArgumentsParser.h"

using namespace MicroScript;

HRESULT ArgumentsParser::start()
{
	if( nullptr == m_begin )
		return E_POINTER;
	m_next = m_begin;
	CHECK( advanceTo( '(' ) );
	m_next++;
	return S_OK;
}

HRESULT ArgumentsParser::next( const char** begin, size_t &length )
{
	CHECK( advance() );
	*begin = m_next;

	while( true )
	{
		if( m_next >= m_end )
			return E_INVALIDARG;
		const char c = *m_next;
		switch( c )
		{
		case ',':
			length = m_next - *begin;
			m_next++;
			return skipTrailingSpaces( begin, length );
		case ')':
			length = m_next - *begin;
			if( length <= 0 )
				return E_INVALIDARG;
			return skipTrailingSpaces( begin, length );
		}

		// Handle escape sequences, "\,", "\)", "\\"
		if( c == '\\' )
		{
			const char nextChar = peek();
			if( nextChar == ',' || nextChar == ')' || nextChar == '\\' )
			{
				m_next += 2;
				continue;
			}
			return E_INVALIDARG;
		}
		m_next++;
	}
	return E_FAIL;
}

HRESULT ArgumentsParser::skipTrailingSpaces( const char** begin, size_t &length )
{
	while( length > 0 && isWhitespace( ( *begin )[ length - 1 ] ) )
		length--;
	return S_OK;
}

HRESULT ArgumentsParser::finish()
{
	CHECK( advance() );
	return ( ')' == *m_next ) ? S_OK : E_INVALIDARG;
}