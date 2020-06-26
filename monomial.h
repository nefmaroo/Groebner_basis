#ifndef GROEBNER_BASIS_MONOMIAL_H
#define GROEBNER_BASIS_MONOMIAL_H

#include <iostream>
#include <vector>
#include <initializer_list>

namespace Groebner {

    class Monomial {
    public:
        using DegreeType = unsigned int;
        using IndexType = size_t;
        using Degrees = std::vector<DegreeType>;
        Monomial() = default;
        Monomial(std::initializer_list<DegreeType> degree_list) : degrees_(degree_list) {
            shrink();
        }
        Monomial(Degrees degree_list) : degrees_(std::move(degree_list)) {
            shrink();
        }
        IndexType numberOfVariables() const;
        DegreeType getTotalDegree() const;
        DegreeType getDegree(IndexType variableIndex) const;
        void setDegree(IndexType variableIndex, DegreeType degree);
        bool checkIfDivisible(const Monomial& other) const;
        Monomial& operator*=(const Monomial& other);
        Monomial operator*(const Monomial& other) const;
        Monomial& operator/=(const Monomial& other);
        Monomial operator/(const Monomial& other) const;
        bool operator==(const Monomial& other) const;
        bool operator!=(const Monomial& other) const;
        friend Monomial lcm(const Monomial& lhv, const Monomial& rhv);
        friend std::ostream& operator<<(std::ostream& out, const Monomial& monomial);
    private:
        void shrink();
        static void printVariable(std::ostream&, IndexType, DegreeType);
        Degrees degrees_;
    };

}

#endif //GROEBNER_BASIS_MONOMIAL_H

