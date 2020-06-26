#include "polynomial_set.h"
#include <boost/rational.hpp>
using boost::rational;
#include <fstream>
#include <ctime>

namespace gb = Groebner;
using gb::Monomial, gb::Term, gb::Polynomial, gb::PolynomialSet, gb::Lex, gb::Deg, gb::LexSum;
using PolynomialIndex = unsigned int;
using Rational = rational<int>;
template<class TFieldType, class Comp>

Polynomial<TFieldType, Comp> constructCyclicPolynomial(PolynomialIndex index, PolynomialIndex n) {
    Monomial::Degrees temp(n, Monomial::DegreeType(0));
    std::fill_n(temp.begin(), index, Monomial::DegreeType(1));
    Polynomial<TFieldType, Comp> f({Term<TFieldType>(Monomial(temp))});
    if (index == n) {
        f += Term<TFieldType>(TFieldType(-1));
        return f;
    }
    for (Monomial::IndexType i = 0; i < n - 1; ++i) {
        temp[i] = 0;
        temp[(i + index) % n] = 1;
        f += Term<TFieldType>(temp);
    }
    return f;
}

template<class TFieldType = Rational, class Comp = Lex>
PolynomialSet<TFieldType, Comp> constructCyclicSet(PolynomialIndex n) {
    PolynomialSet<TFieldType, Comp> cyclicSet;
    for (PolynomialIndex i = 0; i < n; ++i) {
        Polynomial cyclic = constructCyclicPolynomial<TFieldType, Comp>(i + 1, n);
        cyclicSet.getPolynomialSet().insert(std::move(cyclic));
    }
    return cyclicSet;
}

void testCyclic() {
    std::ofstream out("/Users/macbook/Desktop/Groebner.csv");
    double timeinsec1, timeinsec2, timeinsec3;
    for (int i = 1; i < 5; ++i) {
        PolynomialSet cyclic1 = constructCyclicSet(i);
        PolynomialSet<Rational, Deg> cyclic2 = constructCyclicSet<Rational, Deg>(i);
        PolynomialSet<Rational, LexSum<Lex, Deg>> cyclic3 = constructCyclicSet<Rational, LexSum<Lex, Deg>>(i);

        clock_t start1 = clock();
        cyclic1.constructGroebnerBasis();
        clock_t end1 = clock();
        timeinsec1 = (double) (end1 - start1) / CLOCKS_PER_SEC;

        clock_t start2 = clock();
        cyclic2.constructGroebnerBasis();
        clock_t end2 = clock();
        timeinsec2 = (double) (end2 - start2) / CLOCKS_PER_SEC;

        clock_t start3 = clock();
        cyclic3.constructGroebnerBasis();
        clock_t end3 = clock();
        timeinsec3 = (double) (end3 - start3) / CLOCKS_PER_SEC;

        out  << i << ", " << timeinsec1 << ", " << timeinsec2 << ", " << timeinsec3 << "\n";
    }
}
