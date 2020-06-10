#include "polynomial_set.h"
#include <boost/rational.hpp>
using boost::rational;

void testPolynomialSet() {
    namespace gb = Groebner;
    using gb::Term, gb::Polynomial, gb::PolynomialSet, gb::Lex, gb::Deg, gb::LexSum, gb::PolynomialOrder, gb::TermOrder;
    using Rational = rational<int>;

    // Input/Output test
    std::cout << "1) Test polynomial set input and output:\n";
    Polynomial<Rational, Lex> polynomial1({Term<Rational>(Rational(-2), {1, 20, 0}),
                                           Term<Rational>(Rational(1,2)), Term<Rational>(4, {6, 0, 3, 1})});
    Polynomial<Rational, Lex> polynomial2({Term<Rational>(1, {6, 0, 3, 1}), Term<Rational>(-5, {6, 4, 8})});
    PolynomialSet<Rational, Lex> polynomials({polynomial1, polynomial2});
    std::cout << polynomials << "\n";

    // All S-Polynomials
    std::cout << "2) Test for getting all S-Polynomials:\n";
    typename PolynomialSet<Rational, Lex>::SPolynomials pol = polynomials.getAllSPolynomials();
    for (const Polynomial<Rational, Lex> p : pol)
        std::cout << p << "\n";
    std::cout << "\n\n";

    //Groebner basis
    std::cout << "3) Test for getting Groebner basis for given polynomial set:\n";
    Polynomial<Rational, Lex> polynomial3({Term<Rational>(Rational(2), {2}),
                                           Term<Rational>(Rational(-4), {1}), Term<Rational>(1, {0, 2}),
                                           Term<Rational>(Rational(-4), {0, 1}), Term<Rational>(Rational(3))});
    Polynomial<Rational, Lex> polynomial4({Term<Rational>(Rational(1), {2}),
                                           Term<Rational>(Rational(-2), {1}), Term<Rational>(3, {0, 2}),
                                           Term<Rational>(Rational(-12), {0, 1}), Term<Rational>(Rational(9))});
    PolynomialSet<Rational, Lex> polynomials1({polynomial3, polynomial4});
    std::cout << "Polynomial set1 is\n" << polynomials1 << "\n";
    std::cout << "Groebner basis for set1 is\n" << polynomials1.constructGroebnerBasis() << "\n";
    Polynomial<Rational, Lex> polynomial5({Term<Rational>(Rational(1), {2}), Term<Rational>(Rational(-1), {0, 1})});
    Polynomial<Rational, Lex> polynomial6({Term<Rational>(Rational(1), {3}), Term<Rational>(Rational(-1), {0, 0, 1})});
    PolynomialSet<Rational, Lex> polynomials2({polynomial5, polynomial6});
    std::cout << "Polynomial set2 is\n" << polynomials2 << "\n";
    std::cout << "Groebner basis for set2 is\n" << polynomials2.constructGroebnerBasis() << "\n";

    //Reduced Groebner basis
    std::cout << "4) Test for Groebner basis reduction for given polynomial set:\n";




}


