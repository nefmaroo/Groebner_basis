#ifndef GROEBNER_BASIS_MONOMIAL_H
#define GROEBNER_BASIS_MONOMIAL_H

#include<iostream>
#include<vector>

class Monomial {

public:
    using DegreeType = unsigned int;
    using IndexType = size_t;
    using Degrees = std::vector<DegreeType>;
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
    void shrink();
private:
    Degrees degrees_;
};

#endif //GROEBNER_BASIS_MONOMIAL_H

