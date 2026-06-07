cmake_minimum_required(VERSION 3.30)

if( NOT CMAKE_EXPERIMENTAL_CXX_IMPORT_STD )
	if( ${CMAKE_VERSION} VERSION_GREATER_EQUAL 4.3 )
		set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 451f2fe2-a8a2-47c3-bc32-94786d8fc91b)
	elseif( ${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.30 )
		set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
	endif ()
endif ()

set(PROJECT_NAME "ModernCMakeAppTemplate")
set(LIBRARY_TARGET "ModernCMakeAppInternalLib")
set(APP_TARGET "ModernCMakeApp")

# if this is not set by the user cmake will decide
set(OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# Project name and version
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# enable ccache
find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
	#set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM}) # we dont use the c compiler rn
	set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Enable CTest at the top level so `ctest` discovers tests
include(CTest)

# Include custom CMake modules path (for other helpers)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(DEFAULT_LOGGING_INTERFACE_DIR "${CMAKE_SOURCE_DIR}/external/cppLoggingInterface")
set(LOGIFACE_PATH "" CACHE PATH "Optional path to the cppLoggingInterface repo")

if(LOGIFACE_PATH)
	set(LOGGING_INTERFACE_DIR "${LOGIFACE_PATH}")
else()
	set(LOGGING_INTERFACE_DIR "${DEFAULT_LOGGING_INTERFACE_DIR}")
endif()

if(EXISTS "${LOGGING_INTERFACE_DIR}/CMakeLists.txt")
	add_subdirectory("${LOGGING_INTERFACE_DIR}" cppLoggingInterface)
else()
	message(FATAL_ERROR "Missing logging interface at ${LOGGING_INTERFACE_DIR}; provide the repo there or set LOGIFACE_PATH to another directory.")
endif()

option(ENABLE_LOGGING "Enable header-only logging interface" ON)

option(CLANG_TIDY_ENABLED "Enable Clang-Tidy static analysis" ON)
# disable Clang-Tidy if not using Clang or GCC
if(CLANG_TIDY_ENABLED AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  set(CLANG_TIDY_ENABLED OFF)
endif()
if(CLANG_TIDY_ENABLED)
	# Enable Clang-Tidy if available
	include(ConfigureClangTidy)
endif()

# Add subdirectories for source and tests
add_subdirectory(src)

if(BUILD_TESTING)
	add_subdirectory(tests)
endif()