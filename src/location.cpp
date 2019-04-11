#include <random>
#include <functional>

#include <geo/geo.h>

bool geo::Location::operator==(const geo::Location &rhs) const {
    return latitude == rhs.latitude &&
           longitude == rhs.longitude;
}

bool geo::Location::operator!=(const geo::Location &rhs) const {
    return !(rhs == *this);
}

geo::Location geo::random_location(const geo::Location &upper_bound, const geo::Location &lower_bound) {
    auto lat_min = lower_bound.latitude;
    auto lat_max = upper_bound.latitude;
    std::random_device rd_lat;
    std::default_random_engine eng_lat(rd_lat());
    std::uniform_real_distribution<double> dist_lat{lat_min, lat_max};
    auto gen_lat = std::bind(dist_lat, eng_lat);

    auto lon_min = lower_bound.longitude;
    auto lon_max = upper_bound.longitude;
    std::random_device rd_lon;
    std::default_random_engine eng_lon(rd_lon());
    std::uniform_real_distribution<double> dist_lon{lon_min, lon_max};
    auto gen_lon = std::bind(dist_lon, eng_lon);

    return {gen_lat(), gen_lon()};
}

geo::Location geo::square(const geo::Location &corner, double diag) {
    return geo::move_location(move_location(corner, diag, 180), diag, 90);
}

geo::Location::Location(double latitude, double longitude) : latitude(latitude), longitude(longitude),
                                                             time(0) {}

geo::Location::Location(double time, double latitude, double longitude) : time(time), latitude(latitude),
                                                                          longitude(longitude) {}

bool geo::Location::operator<(const geo::Location &rhs) const {
    return time < rhs.time;
}

bool geo::Location::operator>(const geo::Location &rhs) const {
    return rhs < *this;
}

bool geo::Location::operator<=(const geo::Location &rhs) const {
    return !(rhs < *this);
}

bool geo::Location::operator>=(const geo::Location &rhs) const {
    return !(*this < rhs);
}

geo::Location::Location() = default;

/**
 * Kiloeter literal.
 * @param m Distance in kilometers.
 * @return m.
 */
double geo::literals::operator ""_km(long double km) {
    return static_cast<double>(km);
}

/**
 * Kiloeter literal.
 * @param m Distance in kilometers.
 * @return m.
 */
double geo::literals::operator ""_km(unsigned long long km) {
    return static_cast<double>(km);
}

/**
 * Meter literal.
 * @param m Distance in meters.
 * @return m converted to kilometers.
 */
double geo::literals::operator ""_m(long double m) {
    return static_cast<double>(m / KM);

}

/**
 * Meter literal.
 * @param m Distance in meters.
 * @return m converted to kilometers.
 */
double geo::literals::operator ""_m(unsigned long long m) {
    return m / KM;
}
