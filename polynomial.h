#ifndef GROEBNER_BASIS_POLYNOMIAL_H
#define GROEBNER_BASIS_POLYNOMIAL_H
#include <unordered_set>
#include "term.h"

namespace Groebner {
    template<class TFieldType, class Comp>
    class Polynomial {
    public:
        using Terms = std::unordered_set<Term<TFieldType>, Comp>;
        // where Term<TFieldType> is a key type and Comp is a comparison function to use for all key comparisons of this container
        Polynomial() = default;
        Polynomial(const Terms& polynomial) : polynomial_(polynomial) {
        }
        const Terms& getPolynomial() const;

        Polynomial& operator+=(const Term<TFieldType>& term);
        Polynomial& operator-=(const Term<TFieldType>& term);
        Polynomial& operator*=(const Term<TFieldType>& term);

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
            //
        }
    private:
        Terms polynomial_;
    };
}
#endif //GROEBNER_BASIS_POLYNOMIAL_H
