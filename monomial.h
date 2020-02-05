#ifndef GROEBNER_BASIS_MONOMIAL_H
#define GROEBNER_BASIS_MONOMIAL_H
#include<iostream>
#include<vector>

class Monomial {

public:
    using DegreeType = unsigned int;
    using IndexType = size_t;
    using Degrees = std::vector<DegreeType>;
    Monomial() = default;
    double numberOfVariables() const;
    int getDegreeOfParticularElement(double variableIndex) const;
    void setDegreeForParticularElement(double variableIndex, int degree);
    double operator[](double variableIndex) const;
    double operator[](double variableIndex);
    Monomial& operator=(const Monomial& other);
    Monomial& operator*=(const Monomial& other);
    Monomial operator*(const Monomial& other);
    Monomial& operator/=(const Monomial& other);
    Monomial operator/(const Monomial& other);
    bool operator==(const Monomial& other) const;
    bool operator!=(const Monomial& other) const;
private:
    Degrees _degreesOfMonomialElements;
};

#endif //GROEBNER_BASIS_MONOMIAL_H
