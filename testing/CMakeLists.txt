cmake_minimum_required (VERSION 2.6)

project( testing )

set( SOURCES
	main.cpp
	testing.cpp
  	dictionary_tree_node_testing.cpp
    find_word_testing.cpp
  )

set( HEADERS
	main.h
  	testing.h
 	spell_checker_testing.h
  	dictionary_tree_node_testing.h
    find_word_testing.h
  )

include_directories( ${SPELL_CHECKER_INCLUDE} )

add_executable( testing ${SOURCES} ${HEADERS} )

target_link_libraries( testing spell_checker_lib )
