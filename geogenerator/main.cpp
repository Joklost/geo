#include <string>

#include <geo/geo.h>
#include <geo/generator.h>
#include <iostream>

int main(int argc, char *argv[]) {
    for (auto i = 4; i < 17; ++i) {
        geo::Location l{14.629740,121.103266};
        std::string gridlog{"gridlog"};
        gridlog.append(std::to_string(i));
        gridlog.append(".txt");
        std::cout << "Generating " << gridlog << std::endl;
        grid(l, i, 385_m, 100000.0, 20000.0, gridlog.c_str());
    }
}