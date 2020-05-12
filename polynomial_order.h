#ifndef GROEBNER_BASIS_POLYNOMIAL_ORDER_H
#define GROEBNER_BASIS_POLYNOMIAL_ORDER_H
#include "polynomial.h"
#include "term_order.h"

namespace Groebner {
    template<class Comp>
    class PolynomialOrder {
    public:
        template<class TFieldType, class OtherComp>
        static bool cmp(const Polynomial <TFieldType, OtherComp>& lhv, const Polynomial <TFieldType, OtherComp>& rhv);

        // if orderType(lhv, rhv) is true => lhv > rhv
        template<class TFieldType, class OtherComp>
        bool
        operator()(const Polynomial <TFieldType, OtherComp>& lhv, const Polynomial <TFieldType, OtherComp>& rhv) const;
    };

    template<class Comp>
    template <class TFieldType, class OtherComp>
    bool PolynomialOrder<Comp>::cmp(const Polynomial<TFieldType, OtherComp>& lhv, const Polynomial<TFieldType, OtherComp>& rhv) {
        unsigned int min_size = std::min(lhv.numberOfTerms(), rhv.numberOfTerms());
        for (unsigned int index = 0; index < min_size; ++index) {
            if (lhv.getTerm(index) != rhv.getTerm(index))
                return TermOrder<Comp>::cmp(lhv.getTerm(index), rhv.getTerm(index));
        }
        return lhv.numberOfTerms() > rhv.numberOfTerms();
    }

    template<class Comp>
    template <class TFieldType, class OtherComp>
    bool PolynomialOrder<Comp>::operator()(const Polynomial<TFieldType, OtherComp>& lhv, const Polynomial<TFieldType, OtherComp>& rhv) const {
        return PolynomialOrder<Comp>::cmp(lhv, rhv);
    }
}

#endif //GROEBNER_BASIS_POLYNOMIAL_ORDER_H
