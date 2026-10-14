#pragma once
#include <cmath>
class Option {
    private:
        double Stock_Price;
        double Strike_Price;
        double Risk_Free_Rate;
        double Volatility;
        double Maturity_Time;
    public:
        Option(double stock_price, double strike_price, double risk_free_rate, double volatility, double maturity_time)
            : Stock_Price(stock_price), Strike_Price(strike_price), Risk_Free_Rate(risk_free_rate), Volatility(volatility), Maturity_Time(maturity_time) {}

        double getStockPrice() const { return Stock_Price; }
        double getStrikePrice() const { return Strike_Price; }
        double getRiskFreeRate() const { return Risk_Free_Rate; }
        double getVolatility() const { return Volatility; }
        double getMaturityTime() const { return Maturity_Time; }
    protected:
        void setStockPrice(double stock_price) { Stock_Price = stock_price; }
        void setStrikePrice(double strike_price) { Strike_Price = strike_price; }
        void setRiskFreeRate(double risk_free_rate) { Risk_Free_Rate = risk_free_rate; }
        void setVolatility(double volatility) { Volatility = volatility; }
        void setMaturityTime(double maturity_time) { Maturity_Time = maturity_time; }
        void callPrice(double price) { /* IMPLEMENT the call price */ }

    
};

class EuropeanCallOption : public Option {
    public:
        EuropeanCallOption(double stock_price, double strike_price, double risk_free_rate, double volatility, double maturity_time)
            : Option(stock_price, strike_price, risk_free_rate, volatility, maturity_time) {}

        double price() const;
        double getPayOff(double stock_price) const {
            return std::max(0.0, stock_price - getStrikePrice());
        }
};

class EuropeanPutOption : public Option {
    public:
        EuropeanPutOption(double stock_price, double strike_price, double risk_free_rate, double volatility, double maturity_time)
            : Option(stock_price, strike_price, risk_free_rate, volatility, maturity_time) {}

        double price() const;
        double getPayOff(double stock_price) const {
            return std::max(0.0, getStrikePrice() - stock_price);
        }
};