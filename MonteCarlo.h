#include <cmath>
#include "GeomBrownianMotion.h"

namespace MonteCarlo {

    inline double simulateAsianOptionPrice(double S0, double K, double r, double sigma, double T, int numPaths, int numSteps) {
        double dt = T / numSteps;
        double sumPayoffs = 0.0;

        for (int i = 0; i < numPaths; ++i) {
            double S = S0;
            double sumS = 0.0;

            for (int j = 0; j < numSteps; ++j) {
                S = GeomBrownianMotion::simulate(S, r, sigma, dt, dt);
                sumS += S;
            }

            double averageS = sumS / numSteps;
            double payoff = std::max(0.0, averageS - K);
            sumPayoffs += payoff;
        }

        double discountedPayoff = (sumPayoffs / numPaths) * std::exp(-r * T);
        return discountedPayoff;
    }

}