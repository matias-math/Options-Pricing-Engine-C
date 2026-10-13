#pragma once

#include <cmath>
#include <stdlib.h>

//We implement the class BlackScholes, where we use closed-form Black-Scholes formulas for European Call and Put options.



namespace BlackScholes {



    inline double CDF(double x) {
        return std::erfc(-x / std::sqrt(2.0)) / 2.0; 
    }


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


    
};
    

