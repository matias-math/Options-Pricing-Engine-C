#include <iostream>
#include <fstream> 
#include <vector>
#include "black_scholes.h"
#include "MonteCarlo.h"

int main() {
    double S0 = 100.0;
    double r = 0.05;
    double T = 1.0;   
    int numPaths = 10000; 
    int numSteps = 252;   

    std::ofstream file("data.csv");
    file << "Volatility,Strike,Price_CV,stdError\n"; 

    std::cout << "Generating high-density dataset..." << std::endl;

    for (double T_test = 0.25; T_test <= 3.0; T_test += 0.25) {
        
        for (double sigma = 0.05; sigma <= 1.00; sigma += 0.02) {
            
            for (double K = 50.0; K <= 150.0; K += 2.0) {
                
                MonteCarlo::SimulationResult result = MonteCarlo::simulateAsianOptionPrice(
                    S0, K, r, sigma, T_test, numPaths, numSteps
                );

                file << T_test << ","
                        << sigma << "," 
                        << K << "," 
                        << result.price << "," 
                        << result.stdError << "\n";
            }
        }
    }

    file.close();
    std::cout << "\nData saved to 'data.csv'." << std::endl;

    return 0;
}