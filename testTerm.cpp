#include "term.h"
#include "monomial.h"
#include "monomial_order.h"
#include "term_order.h"
#include <boost/rational.hpp>
using boost::rational;

void testTerm() {
    namespace gb = Groebner;
    using gb::Monomial, gb::Term, gb::Lex, gb::Deg, gb::LexSum, gb::TermComparisson;

    // input/output and get-methods test
    std::cout << "1) Test term input:\n";
    Monomial monomial1({5, 4, 0, 1, 0, 0}), monomial2({0, 2, 2, 3, 5});
    Term term1(-2, monomial1), term2(9, monomial2);
    std::cout << "term1 is " << term1 << "\n";
    std::cout << "The monomial of term1 is " << term1.getMonomial() << "\n";
    std::cout << "The coefficient of term1 is " << term1.getCoefficient() << "\n";
    std::cout << "term2 is " << term2 << "\n";
    std::cout << "The monomial of term2 is " << term2.getMonomial() << "\n";
    std::cout << "The coefficient of term2 is " << term2.getCoefficient() << "\n\n";

    // test with boost rational library
    std::cout << "2) Test of boost/rational library usage:\n";
    rational<int> half(1,2);
    rational<int> two(2);
    Term term3(half, monomial1), term4(two, monomial2);
    std::cout << "term3 is " << term3 << "\n";
    std::cout << "term4 is " << term4 << "\n\n";

    // test arithmetic operations
    std::cout << "3) Test term arithmetic operations:\n";
    std::cout << "term1 * term2 =  " << term1 * term2 << "\n\n";
    term1 *= term2;
    std::cout << "term1 *= term2: \n" << "term1 = " << term1 <<"\n\n";
    std::cout << "term3 / term4 =  " << term3 / term4 << "\n\n";
    term3 /= term4;
    std::cout << "term3 /= term4: \n" << "term3 = " << term3 << "\n\n";

    // comparison test
    std::cout << "4) Test for term comparison:\n";
    Monomial monomial4({1, 3, 0, 0}), monomial5({1, 3}), monomial6({5, 0, 3});
    Term term5(2, monomial4), term6(2, monomial5), term7(-2, monomial5), term8(2, monomial6);
    std::cout << "term5 is " << term5 << "\n";
    std::cout << "term6 is " << term6 << "\n";
    if (term5 == term6)
        std::cout << "term5 == term6: \n" << "True\n\n";
    std::cout << "term7 is " << term7 << "\n";
    if (term5 != term7)
        std::cout << "term5 == term7: \n" << "False\n\n";
    std::cout << "term8 is " << term8 << "\n";
    if (term5 != term8)
        std::cout << "term5 == term8: \n" << "False\n\n";

    // comparison test for different monomial order
    std::cout << "5) Terms' comparison test for different monomial order:\n";
    Monomial monomial7{5, 0, 0, 4};
    term5.setMonomial(monomial7);
    std::cout << "term5 is " << term5 << "\n";
    std::cout << "term7 is " << term7 << "\n";
    std::cout << "term8 is " << term8 << "\n\n";

    std::cout << "Lexicographic order: \n";
    if (TermComparisson<Lex>::cmp(term5, term7))
        std:: cout << "term5 > term7\n";
    if (TermComparisson<Lex>::cmp(term8, term5))
        std:: cout << "term5 < term8\n\n";

    std::cout << "Total degree order: \n";
    if (TermComparisson<Deg>::cmp(term5, term7))
        std:: cout << "term5 > term7\n";
    if (TermComparisson<Deg>::cmp(term5, term8))
        std:: cout << "term5 > term8\n\n";

    std::cout << "Lexicographic, then total degree order: \n";
    if (TermComparisson<LexSum<Lex, Deg>>::cmp(term5, term7))
        std:: cout << "term5 > term7\n";
    if (TermComparisson<LexSum<Lex, Deg>>::cmp(term8, term5))
        std:: cout << "term5 < term8\n\n";


    // test exceptions
    std::cout << "6) Test for exceptions:\n";
    term8.setCoefficient(0);
    std::cout << "term5 is\n coeficient: " << term5.getCoefficient() << ", monomial: {" << term5.getMonomial() << "}\n";
    std::cout << "term8 is\n coeficient: " << term8.getCoefficient() << ", monomial: {" << term8.getMonomial() << "}\n";
    std::cout << "Try to divide term5 by term8:\n" << term5 / term8 << "\n";







}
