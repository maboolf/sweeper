cmake_minimum_required(VERSION 4.3.0)

project(Sweeper VERSION 0.5)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_executable(Sweeper ${sources})
target_include_directories(Sweeper PUBLIC "${../include}")
