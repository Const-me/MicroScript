#pragma once
#include "hresult.hpp"

namespace MicroScript
{
	template<class tArg>
	HRESULT parseArgument( const char* arg, size_t length, tArg& result );
}