# Set the C++ standard and enable compiler features
add_library(${LIBRARY_TARGET} STATIC)
target_compile_features(${LIBRARY_TARGET} PUBLIC cxx_std_23)
target_link_libraries(${LIBRARY_TARGET} PUBLIC logiface)

# Compiler-specific warning options for the library target
target_compile_options(${LIBRARY_TARGET} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# Multi-configuration generator options
if(CMAKE_CONFIGURATION_TYPES)
    target_compile_options(${LIBRARY_TARGET} PRIVATE
        "$<$<CONFIG:Debug>:-g>"
        "$<$<CONFIG:Debug>:-O0>"
        "$<$<CONFIG:RelWithDebInfo>:-g>"
        "$<$<CONFIG:RelWithDebInfo>:-O2>"
        "$<$<CONFIG:Release>:-O3>"
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${APP_TARGET} PRIVATE -fmodules-reduced-bmi)
endif()

# Module files
target_sources(${LIBRARY_TARGET} PRIVATE
    FILE_SET CXX_MODULES
    FILES
        lib_example.cppm
)

# Source files
target_sources(${LIBRARY_TARGET} PRIVATE
    lib_example.cpp
)
