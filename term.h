#pragma once

#include "monomial.h"

namespace Groebner {
    template<class TFieldType>
    class Term {
    public:
        Term() = default;

        Term(TFieldType coefficient, Monomial monomial)
                : coefficient_(std::move(coefficient)), monomial_(std::move(monomial)) {
            reduceMonomial();
        }
        const TFieldType& getCoefficient() const;
        const Monomial& getMonomial() const;
        void setCoefficient(const TFieldType& coefficient);
        void setMonomial(const Monomial& monomial);
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

        template<class Comp>
        static bool cmp(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv);

        template<class Comp>
        bool operator()(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) const;

    private:
        void reduceMonomial();
        TFieldType coefficient_ = TFieldType(0);
        Monomial monomial_ = Monomial();
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
    void Term<TFieldType>::setMonomial(const Monomial& monomial) {
        if (coefficient_ != TFieldType(0))
            monomial_ = monomial;
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
        if (coefficient_ == TFieldType(0))
            monomial_ = Monomial();
    }

    template<class TFieldType>
    template<class Comp>
    bool Term<TFieldType>::cmp(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) {
        if (lhv.getCoefficient() < rhv.getCoefficient())
            return true;
        else if (lhv.getCoefficient() < rhv.getCoefficient())
            return false;
        Comp orderType;
        return orderType(lhv.getMonomial(), rhv.getMonomial());
    }

    template<class TFieldType>
    template<class Comp>
    bool Term<TFieldType>::operator()(const Term<TFieldType>& lhv, const Term<TFieldType>& rhv) const {
        return Comp::cmp(lhv, rhv);
    }


    template<class TFieldType>
    std::ostream& operator<<(std::ostream& out, const Term<TFieldType>& term) noexcept {
        if (term.getCoefficient() == TFieldType(0))
            return out << 0;
        if (term.getCoefficient() == TFieldType(1))
            return out << term.getMonomial();
        if (term.getCoefficient() == TFieldType(-1))
            return out << "-" << term.getMonomial();
        if (term.getMonomial().numberOfVariables() == 0)
            return out << term.getCoefficient();
        return out << term.getCoefficient() << " * " << term.getMonomial();
    }
}




