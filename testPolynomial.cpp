#include <ios>
#include "polynomial.h"
#include "polynomial_order.h"
#include "term_order.h"
#include <boost/rational.hpp>
using boost::rational;

void testPolynomial() {
    namespace gb = Groebner;
    using gb::Term, gb::Polynomial, gb::Lex, gb::Deg, gb::LexSum, gb::PolynomialOrder, gb::TermOrder;
    using Rational = rational<int>;

    // Input/Output test
    std::cout << "1) Test polynomial input and output:\n";
    Polynomial<Rational, Lex> polynomial1({Term<Rational>(Rational(-2), {1, 20, 0}),
                                      Term<Rational>(Rational(1,2)), Term<Rational>(4, {6, 0, 3, 1})});
    std::cout << "polynomial1 is " << polynomial1 << "\n";
    Polynomial<Rational, Lex> polynomial2({Term<Rational>(1, {6, 0, 3, 1}), Term<Rational>(-5, {6, 4, 8})});
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


    // Test comparison for equality for two polynomials
    std::cout << "4) Test comparison operations for polynomial1 and polynomial2\n";
    std::cout << "Is polynomial1 equals polynomial2?\n";
    std::cout << "polynomial1 is " << polynomial1 << "\n" << "polynomial2 is " << polynomial2 << "\n";
    if (polynomial1 != polynomial2)
        std::cout << "Answer: NO\n\n";

    // Test comparison for different order
    std::cout << "5) Comparison test of two polinomial for different monomial order:\n";
    std::cout << "polynomial1 is " << polynomial1 << "\n";
    std::cout << "polynomial2 is " << polynomial2 << "\n\n";
    std::cout << "Lexicographic order: \n";
    PolynomialOrder<Lex> orderTypeLex;
    std::cout << std::boolalpha << "polynomial1 > polynomial2 is " << orderTypeLex(polynomial1, polynomial2) << "\n\n";
    std::cout << "Total degree order: \n";
    PolynomialOrder<Deg> orderTypeDeg;
    std::cout << std::boolalpha << "polynomial1 > polynomial2 is " << orderTypeDeg(polynomial1, polynomial2) << "\n\n";
    std::cout << "LexDeg order: \n";
    PolynomialOrder<LexSum<Lex, Deg>> orderTypeLexDeg;
    std::cout << std::boolalpha << "polynomial1 > polynomial2 is " << orderTypeLexDeg(polynomial1, polynomial2) << "\n\n";
    std::cout << "DegLex order: \n";
    PolynomialOrder<LexSum<Deg, Lex>> orderTypeDegLex;
    std::cout << std::boolalpha << "polynomial1 > polynomial2 is " << orderTypeDegLex(polynomial1, polynomial2) << "\n\n";


    // Test for S-Polynomial calculation
    std::cout << "6) Test for S-Polynomial calculation of polynomial1 and polynomial2\n";
    std::cout << "S-Polynomial of " << polynomial1 << "and " << polynomial2 << "is\n"
    << SPolynomial(polynomial1, polynomial2) << "\n\n";

    // Test for reduction of one polynomial by the other one
    std::cout << "7) Test for reduction of one polynomial by the other one\n";
    Polynomial<Rational> polynomial3({Term<Rational>(Rational(-2), {1, 2, 0}), Term<Rational>(4, {6, 0, 3, 1}),
                                      Term<Rational>(Rational(1), {0, 2, 4, 5})});
    Polynomial<Rational> polynomial4({Term<Rational>(Rational(7), {1, 0, 0}), Term<Rational>(-2, {5, 0, 3, 1}),
                                      Term<Rational>(Rational(5), {0, 2, 1, 3})});
    std::cout << "polynomial3 is " << polynomial3 << "\npolynomial4 is " << polynomial4 <<"\n";
    std::cout << "Reduction of polynomial3 by polynomial4 is " << polynomial3.makeSimpleReduction(polynomial4) << "\n";
    Polynomial<Rational> polynomial5({Term<Rational>(2,{4}),Term<Rational>(-1,{3}),Term<Rational>(5,{2}),Term<Rational>(-8,{1}),Term<Rational>(1)});
    Polynomial<Rational> polynomial6({Term<Rational>(1,{2}),Term<Rational>(-1,{1}),Term<Rational>(1)});
    std::cout << polynomial5.makeSimpleReduction(polynomial6) << "\n";
}


