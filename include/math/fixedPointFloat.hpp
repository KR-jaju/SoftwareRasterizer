#ifndef FIXEDPOINTFLOAT_HPP
#define FIXEDPOINTFLOAT_HPP

#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

typedef class fixedPointFloat
{
    private:
        ll upNumber;
        ll downNumber;
        int sign;
        ll completeNumber;
        int pushNum;
        float real;
        unsigned long long push;
        std::vector<float> factorials;
        unsigned long long power2(int n);
        ll power(fixedPointFloat &ref, int n);
    public:
        fixedPointFloat();
        void setNumber(float n);
        void setNumberbyFixed(ll n);
        void showNumber();
        ll operator* (fixedPointFloat &ref);
        fixedPointFloat& operator*= (fixedPointFloat &ref);
        ll operator/ (fixedPointFloat &ref);
        fixedPointFloat& operator/= (fixedPointFloat &ref);
        ll operator+ (fixedPointFloat &ref);
        fixedPointFloat& operator+= (fixedPointFloat &ref);
        ll operator- (fixedPointFloat &ref);
        fixedPointFloat& operator-= (fixedPointFloat &ref);
        bool operator< (fixedPointFloat &ref);
        bool operator> (fixedPointFloat &ref);
        bool operator<= (fixedPointFloat &ref);
        bool operator>= (fixedPointFloat &ref);
        ll sin();
        ll cos();
        ll tan();
        ll round();
} Float;
#endif