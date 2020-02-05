cmake_minimum_required(VERSION 3.15)
project(Groebner_basis)

set(CMAKE_CXX_STANDARD 14)

add_executable(Groebner_basis main.cpp monomial.cpp monomial.h term.cpp term.h README.md)
