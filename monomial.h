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
        explicit Monomial(std::initializer_list<DegreeType> degree_list) : degrees_(degree_list) {
            shrink();
        }
        IndexType numberOfVariables() const;
        DegreeType getTotalDegree() const;
        DegreeType getDegree(IndexType variableIndex) const;
        void setDegree(IndexType variableIndex, DegreeType degree);
        Monomial& operator*=(const Monomial& other);
        Monomial operator*(const Monomial& other) const;
        Monomial& operator/=(const Monomial& other);
        Monomial operator/(const Monomial& other) const;
        bool operator==(const Monomial& other) const;
        bool operator!=(const Monomial& other) const;
        static void printVariable(std::ostream&, IndexType, DegreeType);
    private:
        void shrink();
        Degrees degrees_;
    };
    std::ostream& operator<<(std::ostream& out, const Monomial& monomial) noexcept;

}

#endif //GROEBNER_BASIS_MONOMIAL_H

