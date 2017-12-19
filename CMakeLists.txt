cmake_minimum_required (VERSION 2.6)
project (ReadSFF)

set(SFF_SOURCES "SFF/Pal.cpp" "SFF/SFFv2.cpp" "SFF/Pal.hpp" "SFF/SFFv2.hpp")
set(SOURCES ${SFF_SOURCES} "ReadSFF.cpp")

include_directories("include")

add_executable(ReadSFF ${SOURCES})
target_link_libraries(ReadSFF "../lib/libpcx")
