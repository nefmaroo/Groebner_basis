#include "monomial.h"

// дописать сообщения к throw

Monomial::IndexType Monomial::numberOfVariables() const
{
    return _degreesOfMonomialElements.size();
}

Monomial::DegreeType Monomial::getDegree(IndexType variableIndex) const {
    if (variableIndex >= numberOfVariables())
        throw;
    return _degreesOfMonomialElements[variableIndex];
}

void Monomial::setDegree(IndexType variableIndex, DegreeType degree) {
    if (variableIndex >= numberOfVariables())
        throw;
    _degreesOfMonomialElements[variableIndex] = degree;
}

Monomial& Monomial::operator=(const Monomial& other) {
    _degreesOfMonomialElements = other._degreesOfMonomialElements;
    return *this;
}

Monomial& Monomial::operator*=(const Monomial& other) {
    if (numberOfVariables() < other.numberOfVariables())
        _degreesOfMonomialElements.resize(other.numberOfVariables());
    for (int i = 0; i < numberOfVariables(); ++i) {
        _degreesOfMonomialElements[i] += other[i];
    }
    return *this;
}

Monomial Monomial::operator*(const Monomial& other) {
    Monomial newMonomial = *this;
    newMonomial *= other;
    return newMonomial;
}

Monomial& Monomial::operator/=(const Monomial& other) {
    for (int i = 0; i < other.numberOfVariables(); ++i) {
        if (_degreesOfMonomialElements[i] < other[i])
            throw;
        _degreesOfMonomialElements[i] -= other[i];
    }
    return *this;
}

Monomial Monomial::operator/(const Monomial& other) {
    Monomial newMonomial = *this;
    newMonomial /= other;
    return newMonomial;
}

bool Monomial::operator==(const Monomial& other) const
{
     return _degreesOfMonomialElements == other._degreesOfMonomialElements;
}

bool Monomial::operator!=(const Monomial& other) const
{
    return !(*this == other);
}

