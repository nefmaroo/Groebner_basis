#include "monomial.h"
#include "tests.h"


void testInputOutput() {
    std::cout << "Test Monomial input:\n";
    Groebner::Monomial monomial1({5, 4, 0, 1, 0, 0}), monomial2({0, 2, 2, 3, 5});
    std::cout << "First monomial is " << monomial1 << "\n";
    std::cout << "Second monomial is " << monomial2 << "\n";
}

void testMathOperations() {

}


