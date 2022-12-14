cmake_minimum_required(VERSION 3.7)
project(tcp_client)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp*" )

add_executable(tcp_client ${SOURCES})

set_property(TARGET tcp_client PROPERTY CXX_STANDART 17)
target_compile_options(tcp_client INTERFACE -Wall -Wextra)
