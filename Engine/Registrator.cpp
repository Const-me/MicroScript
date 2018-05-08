#include "stdafx.h"
#include <unordered_map>
#include "Registrator.h"

namespace
{
	// A global variable won't work because initialization order across CPP files is undefined, depends on linker.
	std::unordered_map<std::string, const MicroScript::iFunction*>& theFunctions()
	{
		static std::unordered_map<std::string, const MicroScript::iFunction*> functions;
		return functions;
	}
}

namespace MicroScript
{
	void registerFunction( const std::string& name, const iFunction& func )
	{
		theFunctions()[ name ] = &func;
	}

	const iFunction* resolveFunction( const std::string& name )
	{
		const auto& functions = theFunctions();
		const auto it = functions.find( name );
		if( it != functions.end() )
			return it->second;
		return nullptr;
	}
}