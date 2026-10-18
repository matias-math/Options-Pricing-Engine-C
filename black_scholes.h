#pragma once

#include <cmath>
#include <stdlib.h>

//We implement the class BlackScholes, where we use closed-form Black-Scholes formulas for European Call and Put options.



namespace BlackScholes {



    inline double CDF(double x) {
        return std::erfc(-x / std::sqrt(2.0)) / 2.0; 
    }

    inline double GeometricAsianCallPrice(double Stock_Price, double Strike_Price, double Risk_Free_Rate, double Volatility, double Maturity_Time, int numSteps) {
        
        double N = static_cast<double>(numSteps);
        
        double adj_vol_sq = (Volatility * Volatility) * (N + 1.0) * (2.0 * N + 1.0) / (6.0 * N * N);
        double adj_vol = std::sqrt(adj_vol_sq);
        
        double mu_A = (Risk_Free_Rate - 0.5 * Volatility * Volatility) * (N + 1.0) / (2.0 * N);
        double mu_hat = mu_A + 0.5 * adj_vol_sq;
        
        double d1_val = (std::log(Stock_Price / Strike_Price) + mu_hat * Maturity_Time) / (adj_vol * std::sqrt(Maturity_Time));
        double d2_val = d1_val - adj_vol * std::sqrt(Maturity_Time);
        
        double expected_G = Stock_Price * std::exp(mu_hat * Maturity_Time);
        
        return std::exp(-Risk_Free_Rate * Maturity_Time) * (expected_G * CDF(d1_val) - Strike_Price * CDF(d2_val));
    }
/* BEFORE CHANGING MY GOAL TOWARDS ASIAN OPTIONS, I IMPLEMENTED THE BLACK-SCHOLES FORMULAS FOR EUROPEAN OPTIONS. I WILL KEEP THIS CODE IN CASE I NEED IT LATER.
    inline double d1(double Stock_Price, double Strike_Price, double Risk_Free_Rate, double Volatility, double Maturity_Time) {
        return (std::log(Stock_Price / Strike_Price) + (Risk_Free_Rate + std::pow(Volatility, 2) / 2) * Maturity_Time) / (Volatility * std::sqrt(Maturity_Time));
    }

    
    inline double d2(double d1_val, double Volatility, double Maturity_Time) {
        return d1_val - Volatility * std::sqrt(Maturity_Time);
    }


    inline double CallPrice(double Stock_Price, double Strike_Price, double Risk_Free_Rate, double Volatility, double Maturity_Time) {
        
        double d1_val = d1(Stock_Price, Strike_Price, Risk_Free_Rate, Volatility, Maturity_Time);
        double d2_val = d2(d1_val, Volatility, Maturity_Time); 

        return Stock_Price * CDF(d1_val) - Strike_Price * std::exp(-Risk_Free_Rate * Maturity_Time) * CDF(d2_val);
    }

    inline double PutPrice(double Stock_Price, double Strike_Price, double Risk_Free_Rate, double Volatility, double Maturity_Time) {
        
        double d1_val = d1(Stock_Price, Strike_Price, Risk_Free_Rate, Volatility, Maturity_Time);
        double d2_val = d2(d1_val, Volatility, Maturity_Time);

        return -Stock_Price * CDF(-d1_val) + Strike_Price * std::exp(-Risk_Free_Rate * Maturity_Time) * CDF(-d2_val);
    }

*/
    
};
    

