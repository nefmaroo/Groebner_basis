#include "monomial.h"

#include <numeric>
#include <cassert>

namespace Groebner {
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
        assert(numberOfVariables() >= other.numberOfVariables() && "Cannot divide one monomial by another one");
        for (IndexType i = 0; i < other.numberOfVariables(); ++i) {
            assert(degrees_[i] >= other.getDegree(i) && "Cannot divide one monomial by another one");
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
        while (!degrees_.empty() && degrees_.back() == 0)
            degrees_.pop_back();
    }

    std::ostream& operator<<(std::ostream& out, const Monomial& monomial) noexcept {

        for (Monomial::IndexType i = 0; i < monomial.numberOfVariables() - 1; ++i) {
            if (monomial.getDegree(i) == 1)
                out << "x_" << i + 1 << " * ";
            else if (monomial.getDegree(i) != 0)
                out << "(x_" << i + 1 << ")" << "^" << monomial.getDegree(i) << " * ";

        }
        Monomial::IndexType lastIndex = monomial.getDegree(monomial.numberOfVariables() - 1);
        if (lastIndex == 1)
            out << "x_" << monomial.numberOfVariables();
        else
            out << "(x_" << monomial.numberOfVariables() << ")" << "^" << lastIndex;
        return out;
    }

}
