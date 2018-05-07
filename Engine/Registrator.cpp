#include "stdafx.h"
#include <unordered_map>
#include "Registrator.h"

namespace
{
	std::unordered_map<std::string, const MicroScript::iFunction*> g_functions;
}

namespace MicroScript
{
	void registerFunction( const std::string& name, const iFunction& func )
	{
		g_functions[ name ] = &func;
	}

	const iFunction* resolveFunction( const std::string& name )
	{
		const auto it = g_functions.find( name );
		if( it != g_functions.end() )
			return it->second;
		return nullptr;
	}
}