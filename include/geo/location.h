#ifndef GEO_LOCATION_H
#define GEO_LOCATION_H

#include <ostream>
#include <cmath>
#include <unordered_map>

namespace geo {

    class Location {
    public:
        Location();

        Location(double latitude, double longitude);

        Location(double time, double latitude, double longitude);

        bool operator==(const Location &rhs) const;

        bool operator!=(const Location &rhs) const;

        bool operator<(const Location &rhs) const;

        bool operator>(const Location &rhs) const;

        bool operator<=(const Location &rhs) const;

        bool operator>=(const Location &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Location &location) {
            os << "Location{latitude: " << std::fixed << location.latitude << ", longitude: "
               << std::fixed << location.longitude << "}";
            return os;
        }

        double time{};
        double latitude{};
        double longitude{};
        std::unordered_map<unsigned long, double> connections{};
    };

    Location random_location(const Location &upper_bound, const Location &lower_bound);

    Location square(const Location &corner, double diag /* kilometers */);

}


#endif //GEO_LOCATION_H
