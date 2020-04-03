#ifndef GROEBNER_BASIS_MONOMIAL_H
#define GROEBNER_BASIS_MONOMIAL_H

#include <iostream>
#include <vector>

namespace Groebner {

    class Monomial {
    public:
        using DegreeType = unsigned int;
        using IndexType = size_t;
        using Degrees = std::vector<DegreeType>;
        Monomial(Degrees degree_list) : degrees_(degree_list) {
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
    private:
        Degrees degrees_;
        void shrink();
    };
    std::ostream& operator<<(std::ostream& out, const Monomial& monomial) noexcept;

}

#endif //GROEBNER_BASIS_MONOMIAL_H

