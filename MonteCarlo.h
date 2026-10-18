#pragma once
#include <cmath>
#include <algorithm>
#include <random>
#include "black_scholes.h"

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
        double sumGeo = 0.0;           
        double sumGeoSquared = 0.0;   
        double sumCrossProduct = 0.0;
        double exactGeoPrice = BlackScholes::GeometricAsianCallPrice(S0, K, r, sigma, T, numSteps);


        int numPairs = numPaths / 2;

        for (int i = 0; i < numPairs; i++) {
            double S1 = S0;
            double S2 = S0;
            double sumS1 = 0.0;
            double sumS2 = 0.0;
            double sumLogS1 = 0.0;
            double sumLogS2 = 0.0;

            for (int j = 0; j < numSteps; j++) {
                double Z = norm(rng);
                S1 *= std::exp(drift + vol * Z);
                sumS1 += S1;
                sumLogS1 += std::log(S1);
                S2 *= std::exp(drift + vol * (-Z));
                sumS2 += S2;
                sumLogS2 += std::log(S2);
            }

            double geometricAvg1 = std::exp(sumLogS1 / numSteps);
            double geometricAvg2 = std::exp(sumLogS2 / numSteps);
            double payoffGeo1 = std::max(0.0, geometricAvg1 - K);
            double payoffGeo2 = std::max(0.0, geometricAvg2 - K);
            double payoffGeoAvg = (payoffGeo1 + payoffGeo2) / 2.0;
            double payoffSum1 = std::max(0.0, (sumS1 / numSteps) - K);
            double payoffSum2 = std::max(0.0, (sumS2 / numSteps) - K);
            double payoffSumAvg = (payoffSum1 + payoffSum2)/2.0;
            sumGeo += payoffGeoAvg;
            sumGeoSquared += payoffGeoAvg * payoffGeoAvg;
            sumPayoffs += payoffSumAvg;    
            sumSquaredPayoffs += payoffSumAvg * payoffSumAvg;
            sumCrossProduct += payoffSumAvg * payoffGeoAvg;
        }
        double meanArit = sumPayoffs / numPairs;
        double meanGeo  = sumGeo / numPairs;

        double varArit = (sumSquaredPayoffs - numPairs * meanArit * meanArit) / (numPairs - 1.0);
        double varGeo  = (sumGeoSquared - numPairs * meanGeo * meanGeo) / (numPairs - 1.0);
        double covariance = (sumCrossProduct - numPairs * meanArit * meanGeo) / (numPairs - 1.0);

        double beta = covariance / varGeo;

        double adjustedMeanArit = meanArit - beta * (meanGeo - exactGeoPrice);

        double adjustedVariance = varArit - (covariance * covariance) / varGeo;



        SimulationResult result;
        result.price = adjustedMeanArit * discountFactor;
        result.stdError = std::sqrt(adjustedVariance / numPairs) * discountFactor;

        return result;
    }
}
