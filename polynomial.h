#ifndef GROEBNER_BASIS_POLYNOMIAL_H
#define GROEBNER_BASIS_POLYNOMIAL_H
#include <set>
#include <iterator>
#include "term.h"
#include "monomial_order.h"
#include "term_order.h"

namespace Groebner {
    template<class TFieldType, class Comp = Lex> //????
    class Polynomial {
    public:
        using Terms = std::set<Term<TFieldType>, TermComparisson<Comp>>;
        // where Term<TFieldType> is a key type and Comp is a comparison function to use for all key comparisons of this container
        using TermIndex = int64_t;
        Polynomial() = default;
        explicit Polynomial(const Terms& polynomial) : polynomial_(polynomial) {
        }
        TermIndex numberOfTerms() const;
        const Term<TFieldType>& getTerm(TermIndex index) const;
        const Term<TFieldType>& getLeadingTerm() const;
        const Terms& getPolynomial() const;

        Polynomial& operator+=(const Term<TFieldType>& term);
        Polynomial& operator-=(const Term<TFieldType>& term);
        Polynomial& operator*=(const Term<TFieldType>& term);

        friend Polynomial& operator*(const Term<TFieldType>& term, const Polynomial& polynomial) {
            Polynomial newPolynomial = polynomial;
            newPolynomial *= term;
            return newPolynomial;
        }

        Polynomial& operator+=(const Polynomial& other);
        friend Polynomial operator+(const Polynomial& lhv, const Polynomial& rhv) {
            Polynomial<TFieldType, Comp> newPolynomial = lhv;
            newPolynomial += rhv;
            return newPolynomial;
        }
        Polynomial& operator-=(const Polynomial& other);
        friend Polynomial operator-(const Polynomial& lhv, const Polynomial& rhv) {
            Polynomial<TFieldType, Comp> newPolynomial = lhv;
            newPolynomial -= rhv;
            return newPolynomial;
        }
        Polynomial& operator*=(const Polynomial& other);
        friend Polynomial operator*(const Polynomial& lhv, const Polynomial& rhv) {
            Polynomial<TFieldType, Comp> newPolynomial = lhv;
            newPolynomial *= rhv;
            return newPolynomial;
        }
        friend bool operator==(const Polynomial& lhv, const Polynomial& rhv) {
            return lhv.polynomial_ == rhv.polynomial_;
        }
        friend bool operator!=(const Polynomial& lhv, const Polynomial& rhv) {
            return !(lhv == rhv);
        }

        friend Polynomial SPolynomial(const Polynomial& lhv, const Polynomial& rhv) {
            Term<TFieldType> lcmOfLeadingMonomials(lcm(lhv.getLeadingTerm(), rhv.getLeadingTerm()));
            return (lcmOfLeadingMonomials / lhv.getLeadingTerm()) * lhv - (lcmOfLeadingMonomials / lhv.getLeadingTerm()) * rhv;
        }
    private:
        Terms polynomial_ = Polynomial();
    };

    template<class TFieldType, class Comp>
    typename Polynomial<TFieldType, Comp>::TermIndex Polynomial<TFieldType, Comp>::numberOfTerms() const {
        return polynomial_.size();
    }

    template<class TFieldType, class Comp>
    const Term<TFieldType>& Polynomial<TFieldType, Comp>::getTerm(TermIndex index) const {
        if (index >= numberOfTerms())
            return Term<TFieldType>();
        return *std::next(polynomial_.begin(), index);
    }

    template<class TFieldType, class Comp>
    const Term<TFieldType>& Polynomial<TFieldType, Comp>::getLeadingTerm() const {
        return getTerm(TermIndex(0)); //assuming that leading term is always at the beginning of the set
    }

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

    template<class TFieldType, class Comp>
    std::ostream& operator<<(std::ostream& out, const Polynomial<TFieldType, Comp>& polynomial) {
        for (const Term<TFieldType>& term : polynomial.getPolynomial()) {
            if (term.getCoefficient() > 0 && term != polynomial.getLeadingTerm())
                out << "+ ";
            out << term << " ";
        }
        return out;
    }
}
#endif //GROEBNER_BASIS_POLYNOMIAL_H
