#ifndef GROEBNER_BASIS_MONOMIAL_ORDER_H
#define GROEBNER_BASIS_MONOMIAL_ORDER_H
#include "monomial.h"

namespace Groebner {
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

    template<class T1, class T2>
    class LexSum {
    public:
        static bool cmp(const Monomial& first, const Monomial& second);
        bool operator()(const Monomial& first, const Monomial& second) const;
    };

    template<class T1, class T2>
    bool LexSum<T1, T2>::cmp(const Monomial& first, const Monomial& second) {
        if (T1::cmp(first, second))
            return true;
        if (T1::cmp(second, first))
            return false;
        return T2::cmp(first, second);
    }

    template<class T1, class T2>
    bool LexSum<T1, T2>::operator()(const Monomial& first, const Monomial& second) const {
        return cmp(first, second);
    }
}

#endif //GROEBNER_BASIS_MONOMIAL_ORDER_H
