#include <iostream>
#include <iomanip>
#include "black_scholes.h"

//Running Test of Black-Scholes (Not being used anymore, but kept for reference)

int main(){

    double spot = 100.0;
    double strike = 100.0;
    double rate = 0.05;
    double vol = 0.20;
    double maturity = 1.0;

    double call = BlackScholes::CallPrice(spot,strike,rate,vol,maturity);
    double put = BlackScholes::PutPrice(spot,strike,rate,vol,maturity);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Vanilla European Call Price: " << call << std::endl;
    std::cout << "Vanilla European Put Price: " << put << std::endl;

}