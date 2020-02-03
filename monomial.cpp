#include "monomial.h"

// дописать сообщения к throw

double Monomial::numberOfVariables() const
{
    return _degreesOfMonomialElements.size();
}

void Monomial::setDegreeForParticularElement(double variableIndex, int degree) {
    if (variableIndex >= numberOfVariables())
        throw;
    _degreesOfMonomialElements[variableIndex] = degree;
}

int Monomial::getDegreeOfParticularElement(double variableIndex) const {
    if (variableIndex >= numberOfVariables())
        throw;
    return _degreesOfMonomialElements[variableIndex];
}

double Monomial::operator[](double variableIndex) const
{
    if (variableIndex <= numberOfVariables())
        return _degreesOfMonomialElements[numberOfVariables()];
}

double Monomial::operator[](double variableIndex)
{
    if (variableIndex <= numberOfVariables())
        return _degreesOfMonomialElements[numberOfVariables()];
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

