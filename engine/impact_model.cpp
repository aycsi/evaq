#include "impact_model.h"
#include <cmath>

ImpactModel::ImpactModel(double temp_coef, double perm_coef) 
    : temp_c(temp_coef), perm_c(perm_coef) {
}

double ImpactModel::temp_impact(uint64_t qty, double px, uint64_t depth) const {
    if (depth == 0) return 0.0;
    double participation = static_cast<double>(qty) / depth;
    return temp_c * px * std::sqrt(participation);
}

double ImpactModel::perm_impact(uint64_t qty, double px, uint64_t depth) const {
    if (depth == 0) return 0.0;
    double participation = static_cast<double>(qty) / depth;
    return perm_c * px * participation;
}
