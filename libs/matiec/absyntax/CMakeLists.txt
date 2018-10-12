cmake_minimum_required(VERSION 3.9)
project(st_checker)

add_library(absyntax absyntax.def absyntax.hh absyntax.cc visitor.hh visitor.cc)
