cmake_minimum_required(VERSION 2.6)

project( spell_checker_lib )

set( SOURCES
  )

set( HEADERS
  dictionary_tree_node.h
  spelling_dictionary.h
  dictionary_option.h
  )

add_library( spell_checker_lib ${SOURCES} ${HEADERS})
