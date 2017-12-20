cmake_minimum_required (VERSION 2.6)
project (ReadSFF)

set(SFF_SOURCES "SFF/Pal.cpp" "SFF/SFFv2.cpp" "SFF/Pal.hpp" "SFF/SFFv2.hpp")
set(SOURCES ${SFF_SOURCES} "ReadSFF.cpp")

include_directories("include")
add_library(libpcx STATIC IMPORTED)

if(WIN32)
    set_target_properties(libpcx PROPERTIES IMPORTED_LOCATION "..\\lib\\libpcx.lib")
elseif(UNIX)
    set_target_properties(libpcx PROPERTIES IMPORTED_LOCATION "../lib/libpcx.a")
endif()

add_executable(ReadSFF ${SOURCES})
target_link_libraries(ReadSFF libpcx)
