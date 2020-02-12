#include "monomial.h"
#include <numeric>
#include <cassert>

// дописать сообщения к throw


Monomial::IndexType Monomial::numberOfVariables() const {
    return degrees_.size();
}


Monomial::DegreeType Monomial::getTotalDegree() const {
    return std::accumulate(degrees_.begin(), degrees_.end(), DegreeType(0));
}

Monomial::DegreeType Monomial::getDegree(IndexType variableIndex) const {
    if (variableIndex >= numberOfVariables())
        return 0;
    return degrees_[variableIndex];
}

void Monomial::setDegree(IndexType variableIndex, DegreeType degree) {
    if (variableIndex >= numberOfVariables())
        degrees_.resize(variableIndex + 1, 0);
    degrees_[variableIndex] = degree;
    shrink();
}

Monomial& Monomial::operator*=(const Monomial& other) {
    if (numberOfVariables() < other.numberOfVariables())
        degrees_.resize(other.numberOfVariables());
    for (IndexType i = 0; i < numberOfVariables(); ++i) {
        degrees_[i] += other.getDegree(i);
    }
    shrink();
    return *this;
}

Monomial Monomial::operator*(const Monomial& other) const {
    Monomial newMonomial = *this;
    newMonomial *= other;
    return newMonomial;
}

Monomial& Monomial::operator/=(const Monomial& other) {
    for (IndexType i = 0; i < other.numberOfVariables(); ++i) {
        assert(degrees_[i] < other.getDegree(i) && "degree of divider can't be less than degree of the dividend");
        degrees_[i] -= other.getDegree(i);
    }
    shrink();
    return *this;
}

Monomial Monomial::operator/(const Monomial& other) const {
    Monomial newMonomial = *this;
    newMonomial /= other;
    return newMonomial;
}

bool Monomial::operator==(const Monomial& other) const {
    return degrees_ == other.degrees_;
}

bool Monomial::operator!=(const Monomial& other) const {
    return !(*this == other);
}

void Monomial::shrink() {
    IndexType i = numberOfVariables() - 1;
    while (degrees_[i] == 0 && i >= 0) {
        degrees_.pop_back();
        --i;
    }
}

