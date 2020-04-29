#ifndef GROEBNER_BASIS_POLYNOMIAL_H
#define GROEBNER_BASIS_POLYNOMIAL_H
#include <unordered_set>
#include "term.h"

namespace Groebner {
    template<class TFieldType, class Comp>
    class Polynomial {
    public:
        using Terms = std::unordered_set<Term<TFieldType>, Comp>;
        // where Term<TFieldType> is a key type and Comp is a comparison function to use for all key comparisons of this container
        Polynomial() = default;
        Polynomial(const Terms& polynomial) : polynomial_(polynomial) {
        }
    private:
        Terms polynomial_;
    };
}
#endif //GROEBNER_BASIS_POLYNOMIAL_H
