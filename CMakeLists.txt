cmake_minimum_required(VERSION 3.0...3.27 FATAL_ERROR)

###########################################
###				  DanteLL				###
###########################################

project(

		DanteLL 
		VERSION 0.0.2
		DESCRIPTION "Dante Logging Library"
		LANGUAGES CXX 

)

###########################################
###			  Project options			###
###########################################

option(DLOG_BUILD_EXAMPLES "Build DanteLL examples" OFF)
option(DLOG_BUILD_TESTS "Build tests" OFF)
option(DLOG_DEFAULT_COMPILER_FLAGS "Let DanteLL specify it's compilation flags" OFF)
option(DLOG_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
option(DLOG_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(DLOG_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
option(DLOG_ENABLE_IPO "Enable IPO/LTO" OFF)
option(DLOG_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
option(DLOG_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
option(DLOG_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
option(DLOG_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(DLOG_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)


mark_as_advanced(
	DLOG_OPT_WARNINGS_AS_ERRORS
	DLOG_OPT_ENABLE_CLANG_TIDY
	DLOG_OPT_ENABLE_CPPCHECK
	DLOG_OPT_ENABLE_IPO
	DLOG_OPT_ENABLE_SANITIZER_ADDRESS
	DLOG_OPT_ENABLE_SANITIZER_LEAK
	DLOG_OPT_ENABLE_SANITIZER_UNDEFINED
	DLOG_OPT_ENABLE_SANITIZER_THREAD
	DLOG_OPT_ENABLE_SANITIZER_MEMORY)

# C++ Standard and policies
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

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Project compiler flags for different build types
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_compile_definitions(__RELEASE__)
else()
	add_compile_definitions(__DIST__)
endif()

include(CMake/PreventInSourceBuild.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
	set(DLOG_SUPPORTS_UBSAN ON)
else()
	set(DLOG_SUPPORTS_UBSAN OFF)
endif()
if(WIN32)
	set(DLOG_SUPPORTS_ASAN OFF)
else()
	set(DLOG_SUPPORTS_ASAN ON)
endif()

if(PROJECT_IS_TOP_LEVEL)
	set(DLOG_OPT_BUILD_EXAMPLES ON)					#TODO
	set(DLOG_OPT_BUILD_TESTS ON)
	set(DLOG_OPT_DEFAULT_COMPILER_FLAGS ON)
	set(DLOG_OPT_WARNINGS_AS_ERRORS OFF)
	set(DLOG_OPT_ENABLE_CLANG_TIDY ON)
	set(DLOG_OPT_ENABLE_CPPCHECK ON)
	set(DLOG_OPT_ENABLE_IPO OFF)									#TODO
	set(DLOG_OPT_ENABLE_SANITIZER_ADDRESS ${DLOG_SUPPORTS_ASAN})
	set(DLOG_OPT_ENABLE_SANITIZER_LEAK ON)
	set(DLOG_OPT_ENABLE_SANITIZER_UNDEFINED ${DLOG_SUPPORTS_UBSAN})
	set(DLOG_OPT_ENABLE_SANITIZER_THREAD ON)
	set(DLOG_OPT_ENABLE_SANITIZER_MEMORY ON)
else()
	set(DLOG_OPT_BUILD_EXAMPLES ${DLOG_BUILD_EXAMPLES})
	set(DLOG_OPT_BUILD_TESTS ${DLOG_BUILD_TESTS})
	set(DLOG_OPT_DEFAULT_COMPILER_FLAGS ${DLOG_DEFAULT_COMPILER_FLAGS})
	set(DLOG_OPT_WARNINGS_AS_ERRORS ${DLOG_WARNINGS_AS_ERRORS})
	set(DLOG_OPT_ENABLE_CLANG_TIDY ${DLOG_ENABLE_CLANG_TIDY})
	set(DLOG_OPT_ENABLE_CPPCHECK ${DLOG_ENABLE_CPPCHECK})
	set(DLOG_OPT_ENABLE_IPO ${DLOG_ENABLE_IPO})
	set(DLOG_OPT_ENABLE_SANITIZER_ADDRESS ${DLOG_ENABLE_SANITIZER_ADDRESS})
	set(DLOG_OPT_ENABLE_SANITIZER_LEAK ${DLOG_ENABLE_SANITIZER_LEAK})
	set(DLOG_OPT_ENABLE_SANITIZER_UNDEFINED ${DLOG_ENABLE_SANITIZER_UNDEFINED})
	set(DLOG_OPT_ENABLE_SANITIZER_THREAD ${DLOG_ENABLE_SANITIZER_THREAD})
	set(DLOG_OPT_ENABLE_SANITIZER_MEMORY ${DLOG_ENABLE_SANITIZER_MEMORY})
endif()

# Apply options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(DLOG_project_warnings INTERFACE)
add_library(DLOG_project_options INTERFACE)

if(${DLOG_OPT_DEFAULT_COMPILER_FLAGS})
	if(NOT ${DLOG_OPT_WARNINGS_AS_ERRORS})
		message("###################################################################")
		message("#   Warning: compiler warnings not treated as errors              #")
		message("#   It is recommended to set this option to ON                    #")
		message("###################################################################")
	endif()

	include(CMake/CompilerWarnings.cmake)
	set_project_warnings(
		DLOG_project_warnings ${DLOG_WARNINGS_AS_ERRORS}
		"" "" "" ""
	)
endif()

include(CMake/ClangTidy.cmake)
if(DLOG_OPT_ENABLE_CLANG_TIDY)
	DLOG_enable_clang_tidy(DLOG_project_options ${DLOG_OPT_WARNINGS_AS_ERRORS})
endif()

include(CMake/CppCheck.cmake)
if(DLOG_OPT_ENABLE_CPPCHECK)
	DLOG_enable_cppcheck(${DLOG_OPT_WARNINGS_AS_ERRORS} "")
endif()

include(CMake/Sanitizers.cmake)
DLOG_enable_sanitizers(
	DLOG_project_options
	${DLOG_OPT_ENABLE_SANITIZER_ADDRESS}
	${DLOG_OPT_ENABLE_SANITIZER_LEAK}
	${DLOG_OPT_ENABLE_SANITIZER_UNDEFINED}
	${DLOG_OPT_ENABLE_SANITIZER_THREAD}
	${DLOG_OPT_ENABLE_SANITIZER_MEMORY})

if(PROJECT_IS_TOP_LEVEL)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")
endif()

# library build
add_subdirectory(src)

if(NOT PROJECT_IS_TOP_LEVEL)
	return()
endif()
# only for top level builds


if(DLOG_OPT_BUILD_TESTS)
	add_subdirectory(test)
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT intro)
