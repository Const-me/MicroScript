#pragma once
#include "hresult.hpp"

namespace MicroScript
{
	class ParserBase
	{
	protected:
		const char* const m_begin;
		const char* const m_end;
		const char* m_next;

		template<class fnTest>
		HRESULT advance( fnTest test )
		{
			HRESULT res = S_FALSE;
			while( true )
			{
				if( m_next >= m_end )
					return E_INVALIDARG;
				if( test( *m_next ) )
					return res;
				m_next++;
				res = S_OK;
			}
		}
		inline static bool isWhitespace( char cc )
		{
			return cc == ' ' || cc == '\t';
		}
		HRESULT advanceTo( char c )
		{
			return advance( [ c ]( char cc ) { return c == cc; } );
		}
		HRESULT advance()
		{
			return advance( []( char cc ) { return !isWhitespace( cc ); } );
		}
		char peek() const
		{
			if( m_next + 1 >= m_end )
				return '\0';
			return m_next[ 1 ];
		}

	public:
		ParserBase( const char* begin, size_t length ) :
			m_begin( begin ), m_end( begin + length ), m_next( begin ){ }
	};
}