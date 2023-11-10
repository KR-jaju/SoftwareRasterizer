#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP

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
        int isInf;
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
        void setNumber(int n);
        void showNumber();
        double getReal() const;

        fixedPoint& operator=(fixedPoint const &ref);
        fixedPoint& operator=(int const &n);
        fixedPoint& operator=(ll const &n);
        fixedPoint& operator=(double const &n);
        fixedPoint& operator=(float const &n);

        fixedPoint operator* (fixedPoint ref) const;
        fixedPoint& operator*= (fixedPoint ref);
        fixedPoint operator/ (fixedPoint ref) const;
        fixedPoint& operator/= (fixedPoint ref);
        fixedPoint operator+ (fixedPoint ref) const;
        fixedPoint& operator+= (fixedPoint ref);
        fixedPoint operator- (fixedPoint ref) const;
        fixedPoint operator- () const;
        fixedPoint& operator-= (fixedPoint ref);
        fixedPoint operator% (fixedPoint ref) const;
        fixedPoint& operator%= (fixedPoint ref);

        bool operator< (fixedPoint ref) const;
        bool operator> (fixedPoint ref) const;
        bool operator<= (fixedPoint ref) const;
        bool operator>= (fixedPoint ref) const;
        bool same (fixedPoint ref, double bias) const;

        fixedPoint abs() const;
        fixedPoint sin() const;
        fixedPoint cos() const;
        fixedPoint tan() const;
        fixedPoint round() const;
        fixedPoint sqrt() const;
} _float;
#endif