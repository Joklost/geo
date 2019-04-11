#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>

#include <geo/geo.h>

double geo::deg2rad(const double deg) {
    return (deg * M_PI / 180);
}

geo::Location geo::deg2rad(const geo::Location &pos) {
    auto lat = deg2rad(pos.latitude);
    auto lon = deg2rad(pos.longitude);
    return geo::Location{pos.time, lat, lon};
}

double geo::rad2deg(const double rad) {
    return (rad * 180 / M_PI);
}

geo::Location geo::rad2deg(const geo::Location &pos) {
    auto lat = rad2deg(pos.latitude);
    auto lon = rad2deg(pos.longitude);
    return geo::Location{pos.time, lat, lon};
}

double geo::distance_between(const geo::Location &from, const geo::Location &to) {
    auto u = std::sin((deg2rad(to.latitude) - deg2rad(from.latitude)) / 2);
    auto v = std::sin((deg2rad(to.longitude) - deg2rad(from.longitude)) / 2);
    return 2.0 * EARTH_RADIUS_KM *
           std::asin(std::sqrt(
                   u * u + std::cos(deg2rad(from.latitude)) * std::cos(deg2rad(to.latitude)) * v * v));
}

double geo::bearing_between(const geo::Location &from, const geo::Location &to) {
    auto y = std::sin(deg2rad(to.longitude) - deg2rad(from.longitude)) *
             std::cos(deg2rad(to.latitude));
    auto x = std::cos(deg2rad(from.latitude)) * std::sin(deg2rad(to.latitude)) -
             std::sin(deg2rad(from.latitude)) * std::cos(deg2rad(to.latitude)) *
             std::cos(deg2rad(to.longitude) - deg2rad(from.longitude));
    auto brng = geo::rad2deg(std::atan2(y, x));
    return ((int) brng + 180) % 360;
}

double geo::angle_between(const geo::Location &origin, const geo::Location &pos1, const geo::Location &pos2) {
    std::vector<geo::Location> positions{pos1, pos2};
    std::vector<double> courses;

    auto lat_org = deg2rad(origin.latitude);
    auto lon_org = deg2rad(origin.longitude);

    for (const auto &element : positions) {
        auto lat_pos = deg2rad(element.latitude);
        auto lon_pos = deg2rad(element.longitude);

        auto val = std::atan2(std::sin(lon_org - lon_pos) * std::cos(lat_pos),
                              std::cos(lat_org) * std::sin(lat_pos) -
                              std::sin(lat_org) * std::cos(lat_pos) * std::cos(lon_org - lon_pos));

        courses.emplace_back(std::fmod(val, 2 * M_PI));
    }

    return rad2deg(
            std::acos(std::cos(courses[0]) * std::cos(courses[1]) + std::sin(courses[0]) * std::sin(courses[1])));
}

geo::Location
geo::move_location(const geo::Location &location, double distance, double bearing) {
    auto old_lat = deg2rad(location.latitude);
    auto old_lon = deg2rad(location.longitude);
    auto brng = deg2rad(bearing);

    auto d_r = distance / EARTH_RADIUS_KM;
    auto new_lat = std::asin(std::sin(old_lat) * std::cos(d_r) +
                             std::cos(old_lat) * std::sin(d_r) * std::cos(brng));
    auto new_lon = old_lon + std::atan2(std::sin(brng) * std::sin(d_r) * std::cos(old_lat),
                                        std::cos(d_r) - std::sin(old_lat) * std::sin(new_lat));

    return geo::Location{rad2deg(new_lat), rad2deg(new_lon)};
}

