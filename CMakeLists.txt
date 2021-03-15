cmake_minimum_required(VERSION 3.7)

project(CocoLib
	LANGUAGES CXX
	)

set(CMAKE_CXX_STANDARD 14)

include_directories(Source)
add_subdirectory(Source)
add_subdirectory(Tests)

set_target_properties(CocoLib PROPERTIES LINKER_LANGUAGE CXX)