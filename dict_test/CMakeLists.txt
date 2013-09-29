cmake_minimum_required (VERSION 2.6)

project( dict_test )

set( SOURCES
	main.cpp
  )

set( HEADERS
  )

include_directories( ${SPELL_CHECKER_INCLUDE} )

add_executable( dict_test ${SOURCES} ${HEADERS} )

target_link_libraries( dict_test spell_checker_lib )
