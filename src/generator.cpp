#include <iomanip>

#include <geo/generator.h>
#include <geo/geo.h>

std::vector<std::string> grid(geo::Location &point, unsigned long len, double gap, double time_end, double time_gap) {
    if (time_end <= time_gap && time_end <= 0.0 && time_gap <= 0.0) {
        throw std::runtime_error("time_end and time_gap must be greater than 0");
    }

    std::vector<std::string> lines{};

    auto time = 0.0;

    while (time <= time_end) {
        auto p = point;
        auto l = p;
        auto id = 1;
        for (auto i = 0; i < len; i++) {
            std::ostringstream l1{};
            l1 << id++ << "," << std::fixed << p.latitude << "," << p.longitude << "," << time;
            lines.push_back(l1.str());
            p = geo::move_location(p, gap, 0);

            for (auto j = 1; j < len; j++) {
                l = geo::move_location(l, gap, 90);
                std::ostringstream l2{};
                l2 << id++ << "," << std::fixed << l.latitude << "," << l.longitude << "," << time;
                lines.push_back(l2.str());
            }

            l = p;
        }

        time += time_gap;
    }

    return lines;
}
