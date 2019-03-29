#include <fstream>
#include <iomanip>

#include <geo/geo.h>

void grid(geo::Location &point, unsigned long len, double gap, double time_end, double time_gap, const char *logpath) {
    if (time_end <= time_gap && time_end <= 0.0 && time_gap <= 0.0) {
        throw std::runtime_error("time_end and time_gap must be greater than 0");
    }

    if (!logpath) {
        throw std::runtime_error("no logpath supplied");
    }

    std::ofstream logfile{logpath};

    if (!logfile.is_open()) {
        throw std::runtime_error("failed to open file on logpath");
    }

    auto time = 0.0;

    while (time <= time_end) {
        auto p = point;
        auto l = p;
        auto id = 1;
        for (auto i = 0; i < len; i++) {
            logfile << id++ << "," << std::fixed << p.get_latitude() << "," << p.get_longitude() << "," << time << std::endl;
            p = geo::move_location(p, gap, 0);

            for (auto j = 1; j < len; j++) {
                l = geo::move_location(l, gap, 90);
                logfile << id++ << "," << std::fixed << l.get_latitude() << "," << l.get_longitude() << "," << time << std::endl;
            }

            l = p;
        }

        time += time_gap;
    }
}
