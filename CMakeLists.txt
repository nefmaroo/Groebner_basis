cmake_minimum_required(VERSION 3.15)
project(Groebner_basis)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-I ./boost")
add_executable(Groebner_basis main.cpp monomial.cpp monomial.h term.h README.md monomial_order.cpp monomial_order.h test.cpp)
