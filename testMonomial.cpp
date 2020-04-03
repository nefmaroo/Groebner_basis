#include "monomial.h"

void testMonomial() {

    // input/output test
    std::cout << "1) Test monomial input:\n";
    Groebner::Monomial monomial1({5, 4, 0, 1, 0, 0}), monomial2({0, 2, 2, 3, 5});
    std::cout << "monomial1 is " << monomial1 << "\n";
    std::cout << "monomial2 is " << monomial2 << "\n\n";

    // math operation test
    std::cout << "2) Test monomial operations:\n";
    std::cout << "monomial1 * monomial2 =  " << monomial1 * monomial2 << "\n\n";
    monomial1 *= monomial2;
    std::cout << "monomial1 *= monomial2: \n" << "monomial1 = " << monomial1 <<"\n\n";
    std::cout << "monomial1 / monomial2 =  " << monomial1 / monomial2 << "\n\n";
    monomial1 /= monomial2;
    std::cout << "monomial1 /= monomial2: \n" << "monomial1 = " << monomial1 << "\n\n";

    // complex operations test
    std::cout << "3) Test complex monomial operations:\n";
    Groebner::Monomial monomial3({5, 0, 0, 1});
    std::cout << "monomial1 is " << monomial1 << "\n";
    std::cout << "monomial2 is " << monomial2 << "\n";
    std::cout << "monomial3 is " << monomial3 << "\n";
    std::cout << "monomial1 / monomial3 * monomial2 = " << monomial1 / monomial3 * monomial2 << "\n\n";

    // comparison test
    std::cout << "4) Test for monomial comparison:\n";
    Groebner::Monomial monomial4({1, 3, 0, 0}), monomial5({1, 3}), monomial6({5, 0, 3});
    std::cout << "monomial4 is " << monomial4 << "\n";
    std::cout << "monomial5 is " << monomial5 << "\n";
    std::cout << "monomial6 is " << monomial6 << "\n\n";
    if (monomial4 == monomial5)
        std::cout << "monomial4 == monomial5: \n" << "True\n";
    if (monomial4 != monomial6)
        std::cout << "monomial4 == monomial6: \n" << "False\n\n";

    // test exception
    std::cout << "5) Test exceptions:\n";
    try {
        std::cout << "Try to divide " << monomial4 << " by " << monomial6 << ":\n";
        std::cout << monomial4 / monomial6;
    }
    catch(const std::exception& e) {
        std::cerr << e.what();
    }
}


