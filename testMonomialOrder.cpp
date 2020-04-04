#include "monomial_order.h"
#include "monomial.h"

template<typename OrderType>
void printComparisonResult(const Groebner::Monomial& monomial1, const Groebner::Monomial& monomial2,
        int index1, int index2) {
    std::cout << "monomial" << index1 << " = " << monomial1 << "\n";
    std::cout << "monomial" << index2 << " = " << monomial2 << "\n";
    OrderType orderType;
    if (orderType(monomial1, monomial2))
        std::cout << "Result: monomial" << index1 << " > monomial" << index2 << "\n\n";
    else
        std::cout << "Result: monomial" << index1 << " < monomial" << index2 << "\n\n";
}

void testMonomialOrder() {
    Groebner::Monomial monomial1({5, 4, 0, 1, 0, 0}),
    monomial2({0, 2, 2, 3, 5}), monomial3({1, 3, 0, 0});

    //LexOrder
    std::cout << "1) Lexicographic order comparison: \n";
    printComparisonResult<Groebner::Lex>(monomial1, monomial2, 1, 2);
    printComparisonResult<Groebner::Lex>(monomial2, monomial3, 3, 2);
    printComparisonResult<Groebner::Lex>(monomial1, monomial3,1, 3);

    //DegOrder
    std::cout << "2) Total degree order comparison: \n";
    printComparisonResult<Groebner::Deg>(monomial1, monomial2, 1, 2);
    printComparisonResult<Groebner::Deg>(monomial2, monomial3, 3, 2);
    printComparisonResult<Groebner::Deg>(monomial1, monomial3,1, 3);

    //LexDegOrder
    std::cout << "3) Comparison made first by lexicographic order, then by total degree order: \n";
    printComparisonResult<Groebner::LexSum<Groebner::Deg, Groebner::Lex>>(monomial1, monomial2, 1, 2);
    printComparisonResult<Groebner::LexSum<Groebner::Deg, Groebner::Lex>>(monomial2, monomial3, 3, 2);
    printComparisonResult<Groebner::LexSum<Groebner::Deg, Groebner::Lex>>(monomial1, monomial3, 1, 3);

    //DegLexOrder
    std::cout << "4) Comparison made first by total degree order, then by lexicographic order: \n";
    printComparisonResult<Groebner::LexSum<Groebner::Lex, Groebner::Deg>>(monomial1, monomial2, 1, 2);
    printComparisonResult<Groebner::LexSum<Groebner::Lex, Groebner::Deg>>(monomial2, monomial3, 3, 2);
    printComparisonResult<Groebner::LexSum<Groebner::Lex, Groebner::Deg>>(monomial1, monomial3, 1, 3);

}



