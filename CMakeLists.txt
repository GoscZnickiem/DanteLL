cmake_minimum_required(VERSION 3.0...3.27 FATAL_ERROR)

project(
		DanteLL 
		VERSION 0.0.1
		DESCRIPTION "Dante Logging Library"
		LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()


add_subdirectory(src)

add_subdirectory(test)
