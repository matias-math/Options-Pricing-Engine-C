#pragma once
#include <cmath>

namespace GeomBrownianMotion {

    inline double simulate(double S0, double mu, double sigma, double T, double dt) {
        int N = static_cast<int>(T / dt);
        double S = S0;
        for (int i = 0; i < N; ++i) {
            double Z = static_cast<double>(rand()) / RAND_MAX; // Generate a random number between 0 and 1
            Z = std::sqrt(-2.0 * std::log(Z)) * std::cos(2.0 * M_PI * Z); // Box-Muller transform to get standard normal variable
            S *= std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * Z);
        }
        return S;
    }

};