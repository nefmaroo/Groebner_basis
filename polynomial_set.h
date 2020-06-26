#ifndef GROEBNER_BASIS_POLYNOMIAL_SET_H
#define GROEBNER_BASIS_POLYNOMIAL_SET_H

#include "polynomial.h"
#include "polynomial_order.h"

namespace Groebner {
    template<class TFieldType, class Comp = Lex>
    class PolynomialSet {
    public:
        using Polynomials = std::set<Polynomial<TFieldType, Comp>, PolynomialOrder<Comp>>;
        using SPolynomials = std::vector<Polynomial<TFieldType, Comp>>;
        using PolynomialIndex = unsigned int;
        PolynomialSet() = default;
        explicit PolynomialSet(const Polynomials& polynomials) : polynomials_(polynomials) {
        }
        PolynomialIndex numberOfPolynomials() const;
        const Polynomial<TFieldType, Comp>& getPolynomial(PolynomialIndex index) const;
        const Polynomials& getPolynomialSet() const;
        Polynomials& getPolynomialSet();
        SPolynomials getAllSPolynomials() const;
        void reduceViaSet(Polynomial<TFieldType, Comp>& sPolynomial) const;
        const PolynomialSet& constructGroebnerBasis();
    private:
        Polynomials polynomials_;
    };

    template<class TFieldType, class Comp>
    typename PolynomialSet<TFieldType, Comp>::PolynomialIndex PolynomialSet<TFieldType, Comp>::numberOfPolynomials() const {
        return polynomials_.size();
    }

    template<class TFieldType, class Comp>
    const Polynomial<TFieldType, Comp>& PolynomialSet<TFieldType, Comp>::getPolynomial(PolynomialIndex index) const {
        if (index >= numberOfPolynomials())
            return Polynomial<TFieldType, Comp>(Term<TFieldType>(0));
        return *std::next(polynomials_.begin(), index);
    }


    template<class TFieldType, class Comp>
    const typename PolynomialSet<TFieldType, Comp>::Polynomials& PolynomialSet<TFieldType, Comp>::getPolynomialSet() const {
        return polynomials_;
    }

    template<class TFieldType, class Comp>
    typename PolynomialSet<TFieldType, Comp>::Polynomials& PolynomialSet<TFieldType, Comp>::getPolynomialSet() {
        return polynomials_;
    }



    template<class TFieldType, class Comp>
    typename PolynomialSet<TFieldType, Comp>::SPolynomials PolynomialSet<TFieldType, Comp>::getAllSPolynomials() const {
        SPolynomials s_polynomials;
        PolynomialOrder<Comp> orderType;
        for (const Polynomial<TFieldType, Comp>& f : getPolynomialSet()) {
            for (const Polynomial<TFieldType, Comp>& g : getPolynomialSet()) {
                if (f != g && orderType(f, g)) {
                    s_polynomials.push_back(SPolynomial(f, g));
                }
            }
        }
        return s_polynomials;
    }

    template<class TFieldType, class Comp>
    void PolynomialSet<TFieldType, Comp>::reduceViaSet(Polynomial<TFieldType, Comp>& sPolynomial) const {
        for (const Polynomial<TFieldType, Comp>& polynomial: getPolynomialSet()) {
            sPolynomial.checkIfReducable(polynomial);
        }
    }

    template<class TFieldType, class Comp>
    const PolynomialSet<TFieldType, Comp>& PolynomialSet<TFieldType, Comp>::constructGroebnerBasis() {
        SPolynomials sPolynomials = getAllSPolynomials();
        for (PolynomialIndex index = 0; index < sPolynomials.size(); ++index) {
            reduceViaSet(sPolynomials[index]);
            if (sPolynomials[index].numberOfTerms() != 0) {
                for (const Polynomial<TFieldType, Comp>& polynomial : getPolynomialSet()) {
                    Polynomial<TFieldType, Comp> p = SPolynomial(polynomial, sPolynomials[index]);
                    //std::cout << p << "\n";
                    if (p.numberOfTerms() != 0)
                        sPolynomials.push_back(p);
                }
                polynomials_.insert(sPolynomials[index]);
            }
        }
        return *this;
    }


    template<class TFieldType, class Comp>
    std::ostream& operator<<(std::ostream& out, const PolynomialSet<TFieldType, Comp>& polynomials) {
        for (const Polynomial<TFieldType, Comp>& polynomial : polynomials.getPolynomialSet()) {
            out << polynomial << "\n";
        }
        return out;
    }

}

#endif //GROEBNER_BASIS_POLYNOMIAL_SET_H
