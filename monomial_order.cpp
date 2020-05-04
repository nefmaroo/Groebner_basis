#include "monomial_order.h"

namespace Groebner {
    bool Lex::cmp(const Monomial& first, const Monomial& second) {
        if (first == second)
            return false;
        Monomial::IndexType variableIndex = 0;
        while (first.getDegree(variableIndex) == second.getDegree(variableIndex))
            ++variableIndex;
        return first.getDegree(variableIndex) > second.getDegree(variableIndex);
    }


    bool Lex::operator()(const Monomial& first, const Monomial& second) const {
        return cmp(first, second);
    }

    bool Deg::cmp(const Monomial& first, const Monomial& second) {
        return first.getTotalDegree() > second.getTotalDegree();
    }


    bool Deg::operator()(const Monomial& first, const Monomial& second) const {
        return cmp(first, second);
    }
}
