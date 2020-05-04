#ifndef GROEBNER_BASIS_TERM_ORDER_H
#define GROEBNER_BASIS_TERM_ORDER_H

#include "term.h"

namespace Groebner {
    template<class Comp>
    class TermComparisson {
    public:
        template<class TFieldType>
        static bool cmp(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);

        template<class TFieldType>
        bool operator()(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) const;
    };

    template<class Comp>
    template<class TFieldType>
    bool TermComparisson<Comp>::cmp(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
        if (lhv.getCoefficient() > rhv.getCoefficient())
            return true;
        else if (lhv.getCoefficient() < rhv.getCoefficient())
            return false;
        Comp orderType;
        return orderType(lhv.getMonomial(), rhv.getMonomial());
    }

    template<class Comp>
    template<class TFieldType>
    bool TermComparisson<Comp>::operator()(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) const {
        return TermComparisson<Comp>::cmp(lhv, rhv);
    }
}

#endif //GROEBNER_BASIS_TERM_ORDER_H
