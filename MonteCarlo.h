#pragma once
#include <cmath>
#include <algorithm>
#include <random>

namespace MonteCarlo {

    struct SimulationResult {
        double price;
        double stdError;
    };

    inline SimulationResult simulateAsianOptionPrice(double S0, double K, double r, double sigma, double T, int numPaths, int numSteps) {
        double dt = T / numSteps;
        
        double drift = (r - 0.5 * sigma * sigma) * dt;
        double vol = sigma * std::sqrt(dt);
        double discountFactor = std::exp(-r * T);
        
        std::mt19937_64 rng(42); 
        std::normal_distribution<double> norm(0.0, 1.0);

        double sumPayoffs = 0.0;
        double sumSquaredPayoffs = 0.0;

        int numPairs = numPaths / 2;

        for (int i = 0; i < numPaths; ++i) {
            double S1 = S0;
            double S2 = S0;
            double sumS1 = 0.0;
            double sumS2 = 0.0;

            for (int j = 0; j < numSteps; ++j) {
                double Z = norm(rng);
                S1 *= std::exp(drift + vol * Z);
                sumS1 += S1;
                S2 *= std::exp(drift + vol * (-Z));
                sumS2 += S2;
            }

            double payoff1 = std::max(0.0, (sumS1 / numSteps) - K);
            double payoff2 = std::max(0.0, (sumS2 / numSteps) - K);
            double payoffAvg = (payoff1 + payoff2)/2.0;
            sumPayoffs += payoffAvg;    
            sumSquaredPayoffs += payoffAvg * payoffAvg;

        }
        double meanPayoff = sumPayoffs / numPairs;
        double variance = (sumSquaredPayoffs - numPairs * meanPayoff * meanPayoff) / (numPairs - 1.0);

        SimulationResult result;
        result.price = meanPayoff * discountFactor;
        result.stdError = std::sqrt(variance / numPairs) * discountFactor;

        return result;
    }
}
