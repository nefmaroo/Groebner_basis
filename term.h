#pragma once

#include "monomial.h"
#include "./boost/rational.hpp"

namespace Groebner {
    template<class TFieldType>
    class Term {
    public:
        explicit Term(const Monomial& monomial, const TFieldType& coefficientType = static_cast<TFieldType>(0)) :
        monomial_(monomial), coefficient_(coefficientType) {
            reduceMonomial();
        }
        const TFieldType& getCoefficient() const;
        const Monomial& getMonomial() const;
        void setCoefficient(const TFieldType& coefficient);
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
        void reduceMonomial();
        TFieldType coefficient_;
        Monomial monomial_;
    };

    template<class TFieldType>
    const TFieldType& Term<TFieldType>::getCoefficient() const {
        return coefficient_;
    }

    template<class TFieldType>
    const Monomial& Term<TFieldType>::getMonomial() const {
        return monomial_;
    }

    template<class TFieldType>
    void Term<TFieldType>::setCoefficient(const TFieldType& coefficient) {
        coefficient_ = coefficient;
        reduceMonomial();
    }

    template<class TFieldType>
    Term<TFieldType>& Term<TFieldType>::operator*=(const Term<TFieldType>& other) {
        coefficient_ *= other.coefficient_;
        monomial_ *= other.monomial_;
        reduceMonomial();
        return *this;
    }


    template<class TFieldType>
    Term<TFieldType>& Term<TFieldType>::operator/=(const Term<TFieldType>& other) {
        assert(other.coefficient_ != 0 && "Division by zero is detected");
        coefficient_ /= other.coefficient_;
        monomial_ *= other.monomial_;
        return *this;
    }

    template<class TFieldType>
    void Term<TFieldType>::reduceMonomial() {
        if (coefficient_ == static_cast<TFieldType>(0))
            monomial_ = Monomial();
    }

    template<class TFieldType>
    std::ostream& operator<<(std::ostream& out, const Term<TFieldType>& term) noexcept {
        switch(term.coefficient_)
        {
            case(static_cast<TFieldType>(0)):
                out << 0;
                break;
            case(static_cast<TFieldType>(1)):
                out << term.getMonomial();
                break;
            case(static_cast<TFieldType>(-1)):
                out << "-" << term.getMonomial();
                break;
            default:
                out << term.getCoefficient() << term.getMonomial();
                break;
        }
        return out;
    }

}




