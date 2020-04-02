#include "monomial_order.h"

bool MonomialOrder::Lex::cmp(const Monomial& first, const Monomial& second) {
    if (first == second)
        return false;
    int nonEqualDegree = 0;
    while (first.getDegree(nonEqualDegree) == second.getDegree(nonEqualDegree))
        ++nonEqualDegree;
    return first.getDegree(nonEqualDegree) < second.getDegree(nonEqualDegree);
}


bool MonomialOrder::Lex::operator()(const Monomial& first, const Monomial& second) const {
    return cmp(first, second);
}

bool MonomialOrder::Deg::cmp(const Monomial& first, const Monomial& second) {
    return first.getTotalDegree() < second.getTotalDegree();
}


bool MonomialOrder::Deg::operator()(const Monomial& first, const Monomial& second) const {
    return cmp(first, second);
}

template <class T1, class T2>
bool MonomialOrder::LexSum<T1, T2>::cmp(const Monomial& first, const Monomial& second){
    if (T1::cmp(first, second))
        return true;
    if (T1::cmp(second, first))
        return false;
    return T2::cmp(first, second);
}

template <class T1, class T2>
bool MonomialOrder::LexSum<T1, T2>::operator()(const Monomial& first, const Monomial& second) const {
    return cmp(first, second);
}