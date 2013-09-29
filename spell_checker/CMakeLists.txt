cmake_minimum_required(VERSION 2.6)

project( spell_checker_lib )

set( SOURCES
  latin_traits.cpp
  )

set( HEADERS

  dictionary_tree_node.h
  spelling_dictionary.h
  dictionary_option.h
  latin_traits.h
  )

add_library( spell_checker_lib ${SOURCES} ${HEADERS})
