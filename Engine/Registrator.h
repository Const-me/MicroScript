#pragma once
#include "Function.hpp"

namespace MicroScript
{
	void registerFunction( const std::string& name, const iFunction& func );

	const iFunction* resolveFunction( const std::string& name );

	template<class... ArgTypes>
	class Registrator
	{
		const Function<ArgTypes...> m_func;

	public:
		Registrator( const std::string& name, HRESULT( __cdecl * pfn )( ArgTypes... ) ) :
			m_func( pfn )
		{
			registerFunction( name, m_func );
		}
	};

	template<class... ArgTypes>
	inline Registrator<ArgTypes...> bindFunction( const char* name, HRESULT( __cdecl * pfn )( ArgTypes... ) )
	{
		return Registrator<ArgTypes...>{ name, pfn };
	}
}

// Macro to register a C function, exposing it to the script engine. All arguments types must have parseArgument<> specialized, see parseArgument.cpp, otherwise it won't link.
#define REGISTER_SCRIPT_FUNC( func ) static const auto reg_##func = MicroScript::bindFunction( #func, &func );