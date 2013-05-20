cmake_minimum_required (VERSION 2.6)

project( testing)

set( SOURCES
  testing.cpp
  dictionary_tree_node_testing.cpp
  )

set( HEADERS
  testing.h
  spell_checker_testing.h
  dictionary_tree_node_testing.h
  )

include_directories( ${SPELL_CHECKER_INCLUDE} )

add_library( testing ${SOURCES} ${HEADERS} )

