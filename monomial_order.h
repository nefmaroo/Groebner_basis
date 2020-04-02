#ifndef GROEBNER_BASIS_MONOMIAL_ORDER_H
#define GROEBNER_BASIS_MONOMIAL_ORDER_H
#include "monomial.h"

class MonomialOrder {
    class Lex {

    public:
        static bool cmp(const Monomial& first, const Monomial& second);
        bool operator()(const Monomial& first, const Monomial& second) const;
    };


    class Deg {

    public:
        static bool cmp(const Monomial& first, const Monomial& second);
        bool operator()(const Monomial& first, const Monomial& second) const;
    };

    template <class T1, class T2>
    class LexSum
    {
        static bool cmp(const Monomial& first, const Monomial& second);
        bool operator()(const Monomial& first, const Monomial& second) const;
    };
};

#endif //GROEBNER_BASIS_MONOMIAL_ORDER_H
