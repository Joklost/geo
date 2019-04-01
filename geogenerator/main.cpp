#include <iostream>
#include <fstream>
#include <string>

#include <geo/geo.h>
#include <geo/generator.h>

int main(int argc, char *argv[]) {
    for (auto i = 4; i < 17; ++i) {
        geo::Location l{14.629740,121.103266};
        std::string gridlog{"gridlog"};
        gridlog.append(std::to_string(i));
        gridlog.append(".txt");
        std::cout << "Generating " << gridlog << std::endl;
        auto lines = grid(l, i, 385_m, 100000.0, 20000.0);

        std::ofstream logfile{gridlog};

        if (!logfile.is_open()) {
            throw std::runtime_error("failed to open file on logpath");
        }

        for (auto &line : lines) {
            logfile << line.append("\n");
        }

        logfile.close();
    }
}