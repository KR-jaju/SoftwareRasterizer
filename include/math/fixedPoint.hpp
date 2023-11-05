#ifndef fixedPoint_HPP
#define fixedPoint_HPP

#include <iostream>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;

typedef class fixedPoint
{
    private:
        ull upNumber;
        ull downNumber;
        double real;
        int sign;
        int pushNum;
    public:
        fixedPoint();
        fixedPoint(int n);
        fixedPoint(ll n);
        fixedPoint(ull n);
        fixedPoint(float n);
        fixedPoint(double n);
        void setNumber(float n);
        void setNumber(double n);
        void setNumber(ll n);
        void showNumber();
        double getReal();
        fixedPoint& operator=(fixedPoint const &ref);
        fixedPoint& operator=(int const &n);
        fixedPoint& operator=(ll const &n);
        fixedPoint& operator=(double const &n);
        fixedPoint& operator=(float const &n);
        fixedPoint operator* (fixedPoint ref);
        fixedPoint& operator*= (fixedPoint ref);
        fixedPoint operator/ (fixedPoint ref);
        fixedPoint& operator/= (fixedPoint ref);
        fixedPoint operator+ (fixedPoint ref);
        fixedPoint& operator+= (fixedPoint ref);
        fixedPoint operator- (fixedPoint ref);
        fixedPoint& operator-= (fixedPoint ref);
        fixedPoint operator% (fixedPoint ref);
        fixedPoint& operator%= (fixedPoint ref);
        bool operator< (fixedPoint ref);
        bool operator> (fixedPoint ref);
        bool operator<= (fixedPoint ref);
        bool operator>= (fixedPoint ref);
        fixedPoint sin();
        fixedPoint cos();
        fixedPoint tan();
        fixedPoint round();
} Float;
#endif