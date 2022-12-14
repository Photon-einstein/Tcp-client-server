cmake_minimum_required(VERSION 3.7)
project(tcp_server)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp*" )

add_executable(tcp_server ${SOURCES})

set_property(TARGET tcp_server PROPERTY CXX_STANDART 17)
target_compile_options(tcp_server INTERFACE -Wall -Wextra)
