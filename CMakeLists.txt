cmake_minimum_required(VERSION 2.8.12)
project(VectorMath)
include_directories(".")
include_directories("Engine")
set(CMAKE_SUPPRESS_REGENERATION true)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options( "-std=c++1z" )
	add_compile_options( "-stdlib=libc++" )
	add_compile_options( "-O3" )
	add_compile_options( "-march=native" )
endif()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

source_group( "Main" FILES "MicroScript.cpp" )

FILE( GLOB ENGINE LIST_DIRECTORIES false "Engine/*" )

source_group( "Engine" FILES ${ENGINE})

add_executable (
	MicroScript
	MicroScript.cpp
	${ENGINE}
)