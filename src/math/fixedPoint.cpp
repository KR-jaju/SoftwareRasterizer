#include "math/fixedPoint.hpp"
#include <cmath>

void displayBit(unsigned long long num)
{
    std::string str = "";
    int cnt = 0;
    unsigned long long mask = 1;
    for (int i = 63; i > -1; i--) {
        cnt++;
        if (num & (mask << i))
            str += "1";
        else
            str += "0";
        if (cnt == 8) {
            cnt = 0;
            str += " ";
        }
    }
    std::cout << "bit: " << str << std::endl;
}

fixedPoint::fixedPoint() {
    this->pushNum = 20;
}

fixedPoint::fixedPoint(int n) {
    this->pushNum = 20;
    this->setNumber(double(n));
}

fixedPoint::fixedPoint(ll n) {
    this->pushNum = 20;
    this->setNumber(double(n));
}

fixedPoint::fixedPoint(ull n) {
    this->pushNum = 20;
    this->setNumber(double(n));
}

fixedPoint::fixedPoint(float n) {
    this->pushNum = 20;
    this->setNumber(n);
}

fixedPoint::fixedPoint(double n) {
    this->pushNum = 20;
    this->setNumber(n);
}

void fixedPoint::setNumber(float n) {
    this->real = n;
    ll p = 1;
    n = n * (p << pushNum);
    if (n < 0) {
        this->sign = -1;
        n *= -1;
    }
    else {
        this->sign = 1;
    }
    ull completenumber;
    completenumber = ull(n);
    ull mask = 1;
    mask = (mask << 32) - 1;
    downNumber = completenumber & mask;
    upNumber = (completenumber & ~mask) >> 32;
}

void fixedPoint::setNumber(double n) {
    this->real = n;
    ll p = 1;
    n = n * (p << pushNum);
    if (n < 0) {
        this->sign = -1;
        n *= -1;
    }
    else {
        this->sign = 1;
    }
    ull completenumber;
    completenumber = ull(n);
    ull mask = 1;
    mask = (mask << 32) - 1;
    downNumber = completenumber & mask;
    upNumber = (completenumber & ~mask) >> 32;
}

void fixedPoint::setNumber(ll n) {
    this->real = (double)n;
    setNumber(this->real);
}

fixedPoint& fixedPoint::operator=(fixedPoint const &ref) {
    this->real = ref.real;
    this->sign = ref.sign;
    this->pushNum = ref.pushNum;
    this->upNumber = ref.upNumber;
    this->downNumber = ref.downNumber;

    return *this;
}

fixedPoint& fixedPoint::operator=(int const &n) {
    fixedPoint ref;

    ref.setNumber(ll(n));
    *this = ref;
    return *this;
}

fixedPoint& fixedPoint::operator=(ll const &n) {
    fixedPoint ref;

    ref.setNumber(n);
    *this = ref;
    return *this;
}

fixedPoint& fixedPoint::operator=(double const &n) {
    fixedPoint ref;

    ref.setNumber(n);
    *this = ref;
    return *this;
}

fixedPoint& fixedPoint::operator=(float const &n) {
    fixedPoint ref;

    ref.setNumber(n);
    *this = ref;
    return *this;
}

void fixedPoint::showNumber() {
    ull mask = 1;
    ull resUpThis = (upNumber << (32 - pushNum)) + (downNumber >> (pushNum));
    ull resDownThis = (downNumber & ((mask << pushNum) - 1));
    std::cout.precision(10);
    std::cout << "real number: " << real << std::endl;
    std::cout << "integer part: " << resUpThis << std::endl;
    std::cout << "decimal part: " << float(resDownThis) / (mask << pushNum) << std::endl;
}

double fixedPoint::getReal() {
    return this->real;
}

fixedPoint fixedPoint::operator*(fixedPoint ref) {
    ull mask = 1;
    fixedPoint result;

    result.upNumber = (this->upNumber * ref.upNumber) << 32;
    result.upNumber += this->upNumber * ref.downNumber + this->downNumber * ref.upNumber;

    ull down = ((this->downNumber) * (ref.downNumber));
    result.downNumber = down;
    result.sign = this->sign * ref.sign;
    result.real = 0;
    result.real = double((result.upNumber << 12) + (result.downNumber >> 20)) / (mask << (pushNum));
    result.real *= result.sign;

    result.setNumber(result.real);
    return result;
}

fixedPoint& fixedPoint::operator*=(fixedPoint ref) {
    fixedPoint res;

    res = *this * ref;
    *this = res;
    return *this;
}

fixedPoint fixedPoint::operator%(fixedPoint ref) {
    ull completThis = ((this->upNumber) << 32) + this->downNumber;
    ull completeRef = (ref.upNumber << 32) + ref.downNumber;
    ull res = completThis % completeRef;
    fixedPoint result;

    result.setNumber(float(res) / (1 << pushNum) * this->sign);
    return result;
}

fixedPoint& fixedPoint::operator%=(fixedPoint ref) {
    *this = *this % ref;
    return *this;
}

fixedPoint fixedPoint::operator/(fixedPoint ref) {
    ull res;
    ull op = (ref.upNumber << 32) + ref.downNumber;
    fixedPoint result;

    res = (this->upNumber << 32) + this->downNumber;
    ull decimal = res / op;
    ull down = res % op;
    
    res = (decimal << pushNum) + (down << pushNum) / op;
    ull mask = 1;
    result.setNumber(this->sign * ref.sign * double(res) / (mask << pushNum));
    return result;
}

fixedPoint& fixedPoint::operator/=(fixedPoint ref) {
    
    *this = this->operator/(ref);
    return *this;
}

fixedPoint fixedPoint::operator+(fixedPoint ref) {
    fixedPoint result;
    
    ll res;

    res = this->sign * ((this->upNumber << 32) + this->downNumber) + ref.sign * ((ref.upNumber << 32) + ref.downNumber);
    result.real = double(res) / (1 << pushNum);
    if (res < 0) {
        result.sign = -1;
        res *= -1;
    }
    else {
        result.sign = 1;
    }
    ull mask = 1;
    ull completenumber;
    completenumber = ull(res);
    mask = (mask << 32) - 1;
    result.downNumber = completenumber & mask;
    result.upNumber = (completenumber & ~mask) >> 32;
    return result;
}

fixedPoint& fixedPoint::operator+=(fixedPoint ref) {
    *this = *this + ref;
    return *this;
}

fixedPoint fixedPoint::operator-(fixedPoint ref) {
    fixedPoint result;
    ll res;

    res = this->sign * ((this->upNumber << 32) + this->downNumber) - ref.sign * ((ref.upNumber << 32) + ref.downNumber);
    result.real = double(res) / (1 << pushNum);
    if (res < 0) {
        result.sign = -1;
        res *= -1;
    }
    else {
        result.sign = 1;
    }
    ull mask = 1;
    ull completenumber;
    completenumber = ull(res);
    mask = (mask << 32) - 1;
    result.downNumber = completenumber & mask;
    result.upNumber = (completenumber & ~mask) >> 32;
    return result;
}

fixedPoint& fixedPoint::operator-=(fixedPoint ref) {
    *this = *this - ref;
    return *this;
}

bool fixedPoint::operator<(fixedPoint ref) {
    ull comThis = (this->upNumber << 32) + this->downNumber;
    ull comRef = (ref.upNumber << 32) + ref.downNumber;
    
    if (this->sign < 0 && ref.sign < 0) {
        return comThis > comRef;
    }
    if (this->sign < 0 && ref.sign > 0) {
        return true;
    }
    if (this->sign > 0 && ref.sign < 0) {
        return false;
    }
    return comThis < comRef;
}

bool fixedPoint::operator<=(fixedPoint ref) {
    ull comThis = (this->upNumber << 32) + this->downNumber;
    ull comRef = (ref.upNumber << 32) + ref.downNumber;
    
    if (this->sign < 0 && ref.sign < 0) {
        return comThis >= comRef;
    }
    if (this->sign < 0 && ref.sign > 0) {
        return true;
    }
    if (this->sign > 0 && ref.sign < 0) {
        return false;
    }
    return comThis <= comRef;
}

bool fixedPoint::operator>(fixedPoint ref) {
    ull comThis = (this->upNumber << 32) + this->downNumber;
    ull comRef = (ref.upNumber << 32) + ref.downNumber;
    
    if (this->sign < 0 && ref.sign < 0) {
        return comThis < comRef;
    }
    if (this->sign < 0 && ref.sign > 0) {
        return true;
    }
    if (this->sign > 0 && ref.sign < 0) {
        return false;
    }
    return comThis > comRef;
}

bool fixedPoint::operator>=(fixedPoint ref) {
    ull comThis = (this->upNumber << 32) + this->downNumber;
    ull comRef = (ref.upNumber << 32) + ref.downNumber;
    
    if (this->sign < 0 && ref.sign < 0) {
        return comThis <= comRef;
    }
    if (this->sign < 0 && ref.sign > 0) {
        return true;
    }
    if (this->sign > 0 && ref.sign < 0) {
        return false;
    }
    return comThis >= comRef;
}

fixedPoint fixedPoint::sin() {
    fixedPoint tmp, res, si, x, x_sqr;

    x.setNumber(M_PI);
    x = *this % x;
    x_sqr = x * x;
    
    si.setNumber(ll(1));
    tmp.setNumber(ll(-11 * 10));
    res = x_sqr / tmp + si;

    tmp.setNumber(ll(9 * 8));
    res = res * x_sqr / tmp - si;

    tmp.setNumber(ll(7 * 6));
    res = res * x_sqr / tmp + si;

    tmp.setNumber(ll(5 * 4));
    res = res * x_sqr / tmp - si;

    tmp.setNumber(ll(3 * 2));
    res = (res * x_sqr / tmp + si) * x;
    return res;
}

fixedPoint fixedPoint::cos() {
    fixedPoint tmp, res, si, x, x_sqr;

    x.setNumber(M_PI);
    x = *this % x;
    x_sqr = x * x;

    si.setNumber(ll(1));
    tmp.setNumber(ll(-10 * 9));
    res = x_sqr / tmp + si;

    tmp.setNumber(ll(8 * 7));
    res = res * x_sqr / tmp - si;

    tmp.setNumber(ll(6 * 5));
    res = res * x_sqr / tmp + si;

    tmp.setNumber(ll(4 * 3));
    res = res * x_sqr / tmp - si;

    tmp.setNumber(ll(2));
    res = res * x_sqr / tmp + si;
    return res;
}

fixedPoint fixedPoint::tan() {
    fixedPoint res;
    res = this->sin() / this->cos();
    return res;
}

fixedPoint fixedPoint::round() {
    ull pivot = 524288;
    ull mask = 1;
    ull down = this->downNumber & ((mask << pushNum) - 1);
    fixedPoint res;

    res = *this;
    if (down >= pivot) {
        res.downNumber -= down;
        res.downNumber += (mask << pushNum);
    }
    else {
        res.downNumber -= down;
    }
    ull complete = (res.upNumber << 32) + res.downNumber;
    res.real = res.sign * double(complete) / (mask << pushNum);
    return res;
}