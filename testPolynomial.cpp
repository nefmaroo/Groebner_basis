#include "polynomial.h"
#include <boost/rational.hpp>
using boost::rational;

void testPolynomial() {
    namespace gb = Groebner;
    using gb::Term, gb::Polynomial, gb::Deg;
    using Rational = rational<int>;

    // Input/Output test
    std::cout << "1) Test polynomial input and output:\n";
    Polynomial<Rational> polynomial1({Term<Rational>(Rational(-2), {1, 2, 0}),
                                      Term<Rational>(Rational(1,2)), Term<Rational>(4, {6, 0, 3, 1})});
    std::cout << "polynomial1 is " << polynomial1 << "\n";
    Polynomial<Rational> polynomial2({Term<Rational>(1, {6, 0, 3, 1}), Term<Rational>(-5, {9, 4, 8})});
    std::cout << "polynomial2 is " << polynomial2 << "\n\n";


    // Test arithmetic operations for polynomials
    std::cout << "2) Test arithmetic operations for polynomial1 and polynomial2\n";
    std::cout << "polynomial1 + polynomial2:\n" << polynomial1 + polynomial2 << "\n\n";
    std::cout << "polynomial1 - polynomial2:\n" << polynomial1 - polynomial2 << "\n\n";
    std::cout << "polynomial2 - polynomial1:\n" << polynomial2 - polynomial1 << "\n\n";
    std::cout << "polynomial1 * polynomial2:\n" << polynomial1 * polynomial2 << "\n\n";

    // Test multiplication of term amd polynomial
    std::cout << "3) Test multiplication of term and polynomial\n";
    Term<Rational> term(10, {0, 2, 4});
    std::cout << "Term is " << term << "\n" << "Polynomial is " << polynomial1 << "\n";
    std::cout << "term * polynomial:\n" << term * polynomial1 << "\n\n";


    // Test comparison operations for polynomials
    std::cout << "4) Test comparison operations for polynomial1 and polynomial2\n";
    std::cout << "Is polynomial1 equals polynomial2?\n";
    std::cout << "polynomial1 is " << polynomial1 << "\n" << "polynomial2 is " << polynomial2 << "\n";
    if (polynomial1 != polynomial2)
        std::cout << "Answer: NO\n\n";

    // Test for S-Polynomial calculation
    std::cout << "5) Test for S-Polynomial calculation of polynomial1 and polynomial2\n";
    std::cout << "S-Polynomial of " << polynomial1 << "and " << polynomial2 << "is\n"
    << SPolynomial(polynomial1, polynomial2);

}


