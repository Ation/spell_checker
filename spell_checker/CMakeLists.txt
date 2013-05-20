cmake_minimum_required(VERSION 2.6)

project( spell_checker)

set( SOURCES
  dictionary_tree_node.cpp
  spelling_dictionary.cpp
  )

set( HEADERS
  dictionary_tree_node.h
  spelling_dictionary.h
  )

add_library( spell_checker ${SOURCES} ${HEADERS})
