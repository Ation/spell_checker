cmake_minimum_required (VERSION 2.6)

project ( spell_checker )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set( SPELL_CHECKER_INCLUDE "${PROJECT_SOURCE_DIR}/spell_checker")

add_subdirectory( spell_checker)
add_subdirectory( testing)
