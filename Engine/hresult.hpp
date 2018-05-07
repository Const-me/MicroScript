#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <stdint.h>

namespace MicroScript
{
	using HRESULT = uint32_t;
	constexpr HRESULT S_OK = 0;
	constexpr HRESULT S_FALSE = 1;

	constexpr HRESULT E_INVALIDARG = 0x80070057L;
	constexpr HRESULT E_NOTIMPL = 0x80004001L;
	constexpr HRESULT E_POINTER = 0x80004003L;
	constexpr HRESULT E_FAIL = 0x80004005L;
}

inline bool FAILED( MicroScript::HRESULT hr )
{
	return ( (int32_t)hr ) < 0;
}
#endif

#define CHECK( expr ) { const HRESULT __hr = ( expr ); if( FAILED( __hr ) ) return __hr; }