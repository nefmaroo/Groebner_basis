#include "monomial.h"

// дописать сообщения к throw

Monomial::IndexType Monomial::numberOfVariables() const
{
    return degrees_.size();
}

Monomial::DegreeType Monomial::getDegree(IndexType variableIndex) const {
    if (variableIndex >= numberOfVariables())
        throw;
    return degrees_[variableIndex];
}

void Monomial::setDegree(IndexType variableIndex, DegreeType degree) {
    if (variableIndex >= numberOfVariables())
        throw;
    degrees_[variableIndex] = degree;
}

Monomial& Monomial::operator=(const Monomial& other) {
    degrees_ = other.degrees_;
    return *this;
}

Monomial& Monomial::operator*=(const Monomial& other) {
    if (numberOfVariables() < other.numberOfVariables())
        degrees_.resize(other.numberOfVariables());
    for (int i = 0; i < numberOfVariables(); ++i) {
        degrees_[i] += other.getDegree(i);
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
        if (degrees_[i] < other.getDegree(i))
            throw;
        degrees_[i] -= other.getDegree(i);
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
     return degrees_ == other.degrees_;
}

bool Monomial::operator!=(const Monomial& other) const
{
    return !(*this == other);
}


