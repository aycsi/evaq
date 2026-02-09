#pragma once

#include <cstdint>

class ImpactModel {
public:
    ImpactModel(double temp_coef, double perm_coef);
    double temp_impact(uint64_t qty, double px, uint64_t depth) const;
    double perm_impact(uint64_t qty, double px, uint64_t depth) const;
    
private:
    double temp_c;
    double perm_c;
};
