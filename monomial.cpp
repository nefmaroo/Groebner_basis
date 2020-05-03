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
        if (degree == 0)
            return;
        if (variableIndex >= numberOfVariables())
            degrees_.resize(variableIndex + 1, 0);
        degrees_[variableIndex] = degree;
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
            assert(degrees_[i] >= other.getDegree(i) && "Cannot divide one monomial by another one"); //add details?
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

    Monomial lcm(const Monomial& lhv, const Monomial& rhv) {
        Monomial result = lhv;
        Monomial::IndexType maxNumberOfVariables = std::max(lhv.numberOfVariables(), rhv.numberOfVariables());
        for (Monomial::IndexType index = 0; index < maxNumberOfVariables; ++index)
            result.setDegree(index, std::max(lhv.getDegree(index), rhv.getDegree(index)));
        return result;
    }

    void Monomial::printVariable(std::ostream& out, IndexType index, DegreeType degree) {
        if (degree == 1)
            out << "x_" << index + 1;
        else if (degree != 0)
            out << "(x_" << index + 1 << ")" << "^" << degree;
    }

    void Monomial::shrink() {
        while (!degrees_.empty() && degrees_.back() == 0)
            degrees_.pop_back();
    }

    std::ostream& operator<<(std::ostream& out, const Monomial& monomial) {
        if (monomial.numberOfVariables() == 0)
            return out << "1";
        Monomial::IndexType index = 0;
        for (; index < monomial.numberOfVariables() - 1; ++index) {
            Monomial::printVariable(out, index, monomial.getDegree(index));
            if (monomial.getDegree(index) != 0)
                out << " * ";
        }
        Monomial::printVariable(out, index, monomial.getDegree(index));
        return out;
    }
}
