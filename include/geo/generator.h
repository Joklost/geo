#ifndef GEO_GENERATOR_H
#define GEO_GENERATOR_H

#include <vector>
#include <string>

#include "location.h"

std::vector<std::string> grid(geo::Location &point, unsigned long len, double gap, double time_end, double time_gap);

#endif /* GEO_GENERATOR_H */
