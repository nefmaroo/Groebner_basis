#ifndef UNTITLED27_TERM_H
#define UNTITLED27_TERM_H

#include "monomial.h"

template<class TFieldType>
class Term {
public:
    TFieldType getCoeffitient() const;
    void setCoeffitient(TFieldType coeff);
    Term<TFieldType>& operator*=(const Term<TFieldType>& other);
    friend Term<TFieldType> operator*(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);
    Term<TFieldType>& operator/=(const Term<TFieldType>& other);
    friend Term<TFieldType> operator/(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);
    friend bool operator==(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);
    friend bool operator!=(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);
private:
    TFieldType coefficient_;
    Monomial monomial_;
};

#endif //UNTITLED27_TERM_H

template<class TFieldType>
TFieldType Term<TFieldType>::getCoeffitient() const {
    return coefficient_;
}

template<class TFieldType>
void Term<TFieldType>::setCoeffitient(TFieldType coeff) {
    coefficient_ = coeff;
}

template<class TFieldType>
Term<TFieldType>& Term<TFieldType>::operator*=(const Term<TFieldType>& other) {
    coefficient_ *= other.coefficient_;
    monomial_ *= other.monomial_;
    return *this;
}

template<class TFieldType>
Term<TFieldType> operator*(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
    Term<TFieldType> newTerm = lhv;
    newTerm *= rhv;
    return newTerm;
}

template<class TFieldType>
Term<TFieldType>& Term<TFieldType>::operator/=(const Term<TFieldType>& other) {
    if (other.coefficient_ != 0) //?
    {
        coefficient_ /= other.coefficient_;
        monomial_ *= other.monomial_;
    }
    return *this;
}

template<class TFieldType>
Term<TFieldType> operator/(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
    Term<TFieldType> newTerm = lhv;
    newTerm /= rhv;
    return newTerm;
}

template<class TFieldType>
bool operator==(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
    return (lhv.coefficient_ == rhv.coefficient_) && (lhv.monomial_ == rhv.monomial_);
}

template<class TFieldType>
bool operator!=(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
    return !(lhv == rhv);
}




