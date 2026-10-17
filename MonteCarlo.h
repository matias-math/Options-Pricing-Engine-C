#pragma once
#include <cmath>
#include <algorithm>
#include <random>

namespace MonteCarlo {

    inline double simulateAsianOptionPrice(double S0, double K, double r, double sigma, double T, int numPaths, int numSteps) {
        double dt = T / numSteps;
        
        double drift = (r - 0.5 * sigma * sigma) * dt;
        double vol = sigma * std::sqrt(dt);
        double discountFactor = std::exp(-r * T);
        
        std::mt19937_64 rng(42); 
        std::normal_distribution<double> norm(0.0, 1.0);

        double sumPayoffs = 0.0;

        for (int i = 0; i < numPaths; ++i) {
            double S = S0;
            double sumS = 0.0;

            for (int j = 0; j < numSteps; ++j) {
                double Z = norm(rng);
                S *= std::exp(drift + vol * Z);
                sumS += S;
            }

            double averageS = sumS / numSteps;
            sumPayoffs += std::max(0.0, averageS - K);
        }

        return (sumPayoffs / numPaths) * discountFactor;
    }
}