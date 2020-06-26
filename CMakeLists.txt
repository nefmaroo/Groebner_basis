cmake_minimum_required(VERSION 3.15)
project(Groebner_basis)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(Groebner_basis main.cpp monomial.cpp monomial.h term.h README.md monomial_order.cpp
        monomial_order.h testMonomial.cpp tests.h testTerm.cpp testMonomialOrder.cpp polynomial.h tests.cpp testPolynomial.cpp term_order.h polynomial_order.h polynomial_set.h testPolynomialSet.cpp testCyclic.cpp)
target_link_libraries(Groebner_basis ${Boost_LIBRARIES})

