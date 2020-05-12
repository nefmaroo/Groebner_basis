#ifndef GROEBNER_BASIS_TERM_ORDER_H
#define GROEBNER_BASIS_TERM_ORDER_H

#include "term.h"

namespace Groebner {
    template<class Comp>
    class TermOrder {
    public:
        template<class TFieldType>
        static bool cmp(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);

        // if orderType(lhv, rhv) is true => lhv > rhv
        template<class TFieldType>
        bool operator()(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) const;
    };

    template<class Comp>
    template<class TFieldType>
    bool TermOrder<Comp>::cmp(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
        Comp orderType;
        return orderType(lhv.getMonomial(), rhv.getMonomial());
    }

    template<class Comp>
    template<class TFieldType>
    bool TermOrder<Comp>::operator()(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) const {
        return TermOrder<Comp>::cmp(lhv, rhv);
    }
}

#endif //GROEBNER_BASIS_TERM_ORDER_H
