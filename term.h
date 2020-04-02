#pragma once

#include "monomial.h"
#include "./boost/rational.hpp"

template<class TFieldType>
class Term {
public:
    const TFieldType& getCoefficient() const;
    void setCoefficient(TFieldType coeff);
    Term& operator*=(const Term<TFieldType>& other);
    friend Term operator*(const Term& lhv, const Term& rhv) {
        Term newTerm = lhv;
        newTerm *= rhv;
        return newTerm;
    }
    Term& operator/=(const Term& other);
    friend Term operator/(const Term& lhv, const Term& rhv) {
        Term newTerm = lhv;
        newTerm /= rhv;
        return newTerm;
    }
    friend bool operator==(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
        return (lhv.coefficient_ == rhv.coefficient_) && (lhv.monomial_ == rhv.monomial_);
    }
    friend bool operator!=(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
        return !(lhv == rhv);
    }
private:
    TFieldType coefficient_;
    Monomial monomial_;
};

template<class TFieldType>
const TFieldType& Term<TFieldType>::getCoefficient() const {
    return coefficient_;
}

template<class TFieldType>
void Term<TFieldType>::setCoefficient(TFieldType coeff) {
    coefficient_ = std::move(coeff);
}

template<class TFieldType>
Term<TFieldType>& Term<TFieldType>::operator*=(const Term<TFieldType>& other) {
    coefficient_ *= other.coefficient_;
    monomial_ *= other.monomial_;
    if (other.coefficient_ == 0)

    return *this;
}


template<class TFieldType>
Term<TFieldType>& Term<TFieldType>::operator/=(const Term<TFieldType>& other) {
    assert(other.coefficient_ != 0 && "Division by zero is detected");
    coefficient_ /= other.coefficient_;
    monomial_ *= other.monomial_;
    return *this;
}




