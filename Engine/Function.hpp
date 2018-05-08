#pragma once
#include "parseArgument.hpp"
#include "ArgumentsParser.h"

namespace MicroScript
{
	// Interface class that invokes specific function, parsing argument list from string.
	class iFunction
	{
	protected:
		// Recursive template function to parse string values, produced by ArgumentsParser, into strongly typed tuple elements
		template<size_t i = 0, typename tTuple>
		static inline HRESULT parse( ArgumentsParser &ps, tTuple& args )
		{
			if constexpr( i < std::tuple_size<tTuple>::value )
			{
				const char* begin;
				size_t length;
				CHECK( ps.next( &begin, length ) );
				CHECK( parseArgument( begin, length, std::get<i>( args ) ) );
				return parse<i + 1>( ps, args );
			}
			else
				return ps.finish();
		}

	public:
		// Parse argument list and run the bound function.
		virtual HRESULT invoke( const char* args, size_t length ) const = 0;
	};

	// Template class that implements iFunction for C function pointer
	template<class... ArgTypes>
	class Function: public iFunction
	{
	public:
		using pfnImpl = HRESULT( __cdecl * )( ArgTypes... );

		Function() = delete;
		Function( pfnImpl fn ) : m_func( fn ) { }

		HRESULT invoke( const char* args, size_t length ) const override
		{
			// Parse arguments into the tuple
			ArgumentsParser ps{ args, length };
			CHECK( ps.start() );
			std::tuple<ArgTypes...> theTuple;
			CHECK( parse( ps, theTuple ) );

			// Invoke the C function pointer
			return std::apply( m_func, std::move( theTuple ) );
		}

	private:
		const pfnImpl m_func;
	};
}