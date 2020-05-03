#include "polynomial.h"
#include "term.h"

namespace Groebner {
    template<class TFieldType, class Comp>
    const typename Polynomial<TFieldType, Comp>::Terms& Polynomial<TFieldType, Comp>::getPolynomial() const {
        return polynomial_;
    }

    template<class TFieldType, class Comp>
    Polynomial<TFieldType, Comp>& Polynomial<TFieldType, Comp>::operator+=(const Term<TFieldType>& term) {
        if (term == TFieldType(0))
            return *this;
        for (const Term<TFieldType>& currentTerm : getPolynomial()) {
            if (currentTerm.getMonomial() == term.getMonomial()) {
                TFieldType newCoefficient = currentTerm.getCoefficient() + term.getCoefficient();
                polynomial_.erase(currentTerm);
                if (newCoefficient != TFieldType(0))
                    polynomial_.insert(Term<TFieldType>(newCoefficient, term.getMonomial()));
                return *this;
            }
        }
        polynomial_.insert(term);
        return *this;
    }

    template<class TFieldType, class Comp>
    Polynomial<TFieldType, Comp>& Polynomial<TFieldType, Comp>::operator-=(const Term<TFieldType>& term) {
        term.setCoefficient(TFieldType(-1) * term.getCoefficient());
        *this += term;
    }

    template<class TFieldType, class Comp>
    Polynomial<TFieldType, Comp>& Polynomial<TFieldType, Comp>::operator*=(const Term<TFieldType>& term) {
        Polynomial<TFieldType, Comp> newPolynomial;
        for (const Term<TFieldType>& currentTerm : getPolynomial())
            newPolynomial += currentTerm * term;
        *this = std::move(newPolynomial);
        return *this;
    }

    template<class TFieldType, class Comp>
    Polynomial<TFieldType, Comp>& Polynomial<TFieldType, Comp>::operator+=(const Polynomial<TFieldType, Comp>& other) {
        for (const Term<TFieldType>& term : other.getPolynomial())
            *this += term;
        return *this;
    }

    template<class TFieldType, class Comp>
    Polynomial<TFieldType, Comp>& Polynomial<TFieldType, Comp>::operator-=(const Polynomial<TFieldType, Comp>& other) {
        for (const Term<TFieldType>& term : other.getPolynomial())
            *this -= term;
        return *this;
    }

    template<class TFieldType, class Comp>
    Polynomial<TFieldType, Comp>& Polynomial<TFieldType, Comp>::operator*=(const Polynomial<TFieldType, Comp>& other) {
        for (const Term<TFieldType>& term : other.getPolynomial())
            *this *= term;
        return *this;
    }

}
