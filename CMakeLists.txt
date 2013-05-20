cmake_minimum_required (VERSION 2.6)

project (spell_test)

set( SOURCES
  main.cpp
  )

set( HEADERS
  main.h
  )

set( SPELL_CHECKER_INCLUDE "${PROJECT_SOURCE_DIR}/spell_checker")

include_directories( ${PELL_CHECKER_INCLUDE}  "${PROJECT_SOURCE_DIR}/testing")

add_subdirectory( spell_checker)
add_subdirectory( testing)

add_executable( spell_test ${SOURCES} ${HEADERS} )
target_link_libraries( spell_test spell_checker testing)
