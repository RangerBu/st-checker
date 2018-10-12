cmake_minimum_required(VERSION 3.9)
project(st_checker)

#include(FindBISON.cmake)
#include(FindFLEX.cmake)
#
#BISON_TARGET(parser iec_bison.yy iec_bison.cc)
#FLEX_TARGET(scanner iec_flex.ll iec_flex.cc)
#ADD_FLEX_BISON_DEPENDENCY(scanner parser)


set(BisonSrc iec_bison.hh iec_bison.cc)

set(FlexSrc iec_flex.cc)

include_directories("../absyntax")

add_library(stage1_2 stage1_2.cc create_enumtype_conversion_functions.cc ${BisonSrc} ${FlexSrc})

#set_source_files_properties(iec_bison.cc PROPERTIES DEPENDS iec_bison.hh)
#set_source_files_properties(${BisonSrc} PROPERTIES DEPENDS parser)
#set_source_files_properties(${FlexSrc} PROPERTIES DEPENDS scanner DEPENDS parser)