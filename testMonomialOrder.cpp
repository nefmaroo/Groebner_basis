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
    namespace gb = Groebner;
    using gb::Monomial, gb::Lex, gb::Deg, gb::LexSum;
    Monomial monomial1({5, 4, 0, 1, 0, 0}),
    monomial2({0, 2, 2, 3, 5}), monomial3({1, 3, 0, 0});

    std::cout << "MonomialOrder class test:\n";

    //LexOrder
    std::cout << "1) Lexicographic order comparison: \n";
    printComparisonResult<Lex>(monomial1, monomial2, 1, 2);
    printComparisonResult<Lex>(monomial2, monomial3, 3, 2);
    printComparisonResult<Lex>(monomial1, monomial3,1, 3);

    //DegOrder
    std::cout << "2) Total degree order comparison: \n";
    printComparisonResult<Deg>(monomial1, monomial2, 1, 2);
    printComparisonResult<Deg>(monomial2, monomial3, 3, 2);
    printComparisonResult<Deg>(monomial1, monomial3,1, 3);

    //LexDegOrder
    std::cout << "3) Comparison made first by lexicographic order, then by total degree order: \n";
    printComparisonResult<LexSum<Lex, Deg>>(monomial1, monomial2, 1, 2);
    printComparisonResult<LexSum<Lex, Deg>>(monomial2, monomial3, 3, 2);
    printComparisonResult<LexSum<Lex, Deg>>(monomial1, monomial3, 1, 3);

}



