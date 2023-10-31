#include "math/fixedPointFloat.hpp"

fixedPointFloat::fixedPointFloat() {
    this->pushNum = 20;
    this->push = power2(pushNum);
    float num = 1;
    for (float i = 1; i <= 7; i++) {
        num *= i;
        factorials.push_back(num);
    }
}

unsigned long long fixedPointFloat::power2(int n) {
    unsigned long long res = 1;

    for (int i = 0; i < n; i++) {
        res *= 2;
    }
    return res;
}

void fixedPointFloat::setNumber(float n) {
    n *= this->push;
    if (n < 0) {
        sign = -1;
        n *= -1;
    }
    else
        sign = 1;
    this->completeNumber = ll(n);
    upNumber = (completeNumber >> 32);
    downNumber = (completeNumber << 32);
    downNumber = (downNumber >> 32);
    this->real = n;
}

void fixedPointFloat::setNumberbyFixed(ll n) {
    if (n < 0) {
        this->completeNumber = -1 * n;
        this->sign = -1;
    }
    else {
        this->completeNumber = n;
        this->sign = 1;
    }
    this->real = this->sign * float(this->completeNumber) / (1 << pushNum);
    upNumber = (completeNumber >> 32);
    downNumber = (completeNumber << 32);
    downNumber = (downNumber >> 32);
}

void fixedPointFloat::showNumber()
{
    ll resUpThis = (upNumber << (32 - pushNum)) + (downNumber >> (pushNum));
    ll resDownThis = (downNumber & (power2(pushNum) - 1));
    std::cout << "integer part: " << resUpThis << std::endl;
    std::cout << "decimal part: " << resDownThis / power2(pushNum) << std::endl;
}

ll fixedPointFloat::operator*(fixedPointFloat &ref) {
    ll res;
    ll resUpThis = (upNumber << (32 - pushNum)) + (downNumber >> (pushNum));
    ll resUpRef = (ref.upNumber << (32 - pushNum)) + (ref.downNumber >> (pushNum));
    ll resDownThis = (downNumber & (power2(pushNum) - 1));
    ll resDownRef = (ref.downNumber & (power2(pushNum) - 1));

    res = (resUpThis * resUpRef) << (pushNum);
    res += (resUpThis * resDownRef + resUpRef * resDownThis);
    res += (resDownRef * resDownThis) >> (pushNum);
    res *= this->sign * ref.sign;
    return res;
}

fixedPointFloat& fixedPointFloat::operator*=(fixedPointFloat &ref) {
    ll res;

    res = this->operator*(ref);
    if (res < 0) {
        this->sign = -1;
        res *= -1;
    }
    else
        this->sign = 1;
    this->completeNumber = res;
    this->upNumber = (completeNumber >> 32);
    this->downNumber = (completeNumber << 32);
    this->downNumber = (downNumber >> 32);
    this->real = float(this->sign * res) / (1 << pushNum);
    return *this;
}

ll fixedPointFloat::operator/(fixedPointFloat &ref) {
    ll res;
    ll resUpThis = (upNumber << (32 - pushNum)) + (downNumber >> (pushNum));
    ll resDownThis = (downNumber & (power2(pushNum) - 1));

    res = ((resUpThis << pushNum) + (resDownThis)) << pushNum;
    res /= ref.completeNumber;
    res *= this->sign * ref.sign;
    return res;
}

fixedPointFloat& fixedPointFloat::operator/=(fixedPointFloat& ref) {
    long long res;

    res = *this / ref;
    if (res < 0) {
        this->sign = -1;
        res *= -1;
    }
    else
        this->sign = 1;
    this->completeNumber = res;
    this->upNumber = (completeNumber >> 32);
    this->downNumber = (completeNumber << 32);
    this->downNumber = (downNumber >> 32);
    this->sign = this->sign * ref.sign;
    this->real = float(this->sign * res) / (1 << pushNum);
    return *this;
}

ll fixedPointFloat::operator+(fixedPointFloat& ref) {
    return (this->sign * this->completeNumber + ref.sign * ref.completeNumber);
}

fixedPointFloat& fixedPointFloat::operator+=(fixedPointFloat& ref) {
    ll res = this->sign * this->completeNumber + ref.sign * ref.completeNumber;

    if (res < 0) {
        this->sign = -1;
        res *= -1;
    }
    else
        this->sign = 1;
    this->completeNumber = res;
    this->upNumber = (completeNumber >> 32);
    this->downNumber = (completeNumber << 32);
    this->downNumber = (downNumber >> 32);
    this->real = float(this->sign * res) / (1 << pushNum);
    return *this;
}

ll fixedPointFloat::operator-(fixedPointFloat& ref) {
    return this->sign * this->completeNumber - ref.sign * ref.completeNumber;
}

fixedPointFloat& fixedPointFloat::operator-=(fixedPointFloat& ref) {
    ll res = this->sign * this->completeNumber - ref.sign * ref.completeNumber;

    if (res < 0)
    {
        this->sign = -1;
        res *= -1;
    }
    else
        this->sign = 1;
    this->completeNumber = res;
    this->upNumber = (completeNumber >> 32);
    this->downNumber = (completeNumber << 32);
    this->downNumber = (downNumber >> 32);
    this->real = float(this->sign * res) / (1 << pushNum);
    return *this;
}

bool fixedPointFloat::operator<(fixedPointFloat &ref) {
    if (this->completeNumber * this->sign < ref.completeNumber * ref.sign)
        return true;
    return false;
}

bool fixedPointFloat::operator<=(fixedPointFloat& ref) {
    if (this->completeNumber * this->sign <= ref.completeNumber * ref.sign)
        return true;
    return false;
}

bool fixedPointFloat::operator>(fixedPointFloat& ref) {
    if (this->completeNumber * this->sign > ref.completeNumber * ref.sign)
        return true;
    return false;
}

bool fixedPointFloat::operator>=(fixedPointFloat& ref) {
    if (this->completeNumber * this->sign >= ref.completeNumber * ref.sign)
        return true;
    return false;
}

ll fixedPointFloat::power(fixedPointFloat &ref, int n) {
    fixedPointFloat res;

    res.setNumber(ref.real);
    for (int i = 1; i < n; i++)
        res *= res;
    return (res.sign * res.completeNumber);
}

ll fixedPointFloat::sin() {
    fixedPointFloat pivot, tmp, res, si, pi, cpy;

    pivot.setNumber(2 * M_PI);
    pi.setNumber(M_PI);
    si.setNumber(180);
    si.setNumberbyFixed(pi / si);
    cpy = *this;
    cpy.setNumberbyFixed(cpy * si);
    if (cpy.completeNumber * cpy.sign < 0) {
        while (cpy.completeNumber * cpy.sign < 0)
            cpy += pivot;
    }
    if (cpy > pivot) {
        while (cpy > pivot)
            cpy -= pivot;
    }
    res = cpy;

    si.setNumberbyFixed(-1 * (power(cpy, 3)));
    tmp.setNumber(factorials[2]);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    si.setNumberbyFixed(power(cpy, 5));
    tmp.setNumber(factorials[4]);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    si.setNumberbyFixed(-1 * power(cpy, 7));
    tmp.setNumber(factorials[6]);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    return res.completeNumber * res.sign;
}

ll fixedPointFloat::cos() {
    fixedPointFloat pivot, tmp, res, si, cpy, pi;

    pivot.setNumber(2 * M_PI);
    pi.setNumber(M_PI);
    si.setNumber(180);
    si.setNumberbyFixed(pi / si);
    cpy = *this;
    cpy.setNumberbyFixed(cpy * si);
    if (cpy.completeNumber * cpy.sign < 0) {
        while (cpy.completeNumber * cpy.sign < 0)
            cpy += pivot;
    }
    if (cpy > pivot) {
        while (cpy > pivot)
            cpy -= pivot;
    }
    res.setNumber(1);

    si.setNumberbyFixed(-1 * (power(cpy, 2)));
    tmp.setNumber(factorials[1]);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    si.setNumberbyFixed(power(cpy, 4));
    tmp.setNumber(factorials[3]);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    si.setNumberbyFixed(-1 * power(cpy, 6));
    tmp.setNumber(factorials[5]);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);
    return res.completeNumber * res.sign;
}

ll fixedPointFloat::tan() {
    fixedPointFloat pivot, tmp, res, si, cpy, pi;

    pivot.setNumber(2 * M_PI);
    pi.setNumber(M_PI);
    si.setNumber(180);
    si.setNumberbyFixed(pi / si);
    cpy = *this;
    cpy.setNumberbyFixed(cpy * si);
    if (cpy.completeNumber * cpy.sign < 0) {
        while (cpy.completeNumber * cpy.sign < 0)
            cpy += pivot;
    }
    if (cpy > pivot) {
        while (cpy > pivot)
            cpy -= pivot;
    }
    res = cpy;

    si.setNumberbyFixed((power(cpy, 3)));
    tmp.setNumber(3);
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    si.setNumber(2);
    tmp.setNumber(15);
    tmp.setNumberbyFixed(si / tmp);
    si.setNumberbyFixed(power(cpy, 5));
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);

    si.setNumber(17);
    tmp.setNumber(375);
    tmp.setNumberbyFixed(si / tmp);
    si.setNumberbyFixed(power(cpy, 7));
    si.setNumberbyFixed(si / tmp);
    res.setNumberbyFixed(res + si);
    return res.completeNumber * res.sign;
}

ll fixedPointFloat::round() {
    fixedPointFloat pivot;
    ll integerNum, decimalNum;

    integerNum = (this->upNumber << pushNum) + (this->downNumber >> pushNum);
    decimalNum = this->downNumber & ((1 << pushNum) - 1);
    pivot.setNumber(0.5);

    if (decimalNum >= pivot.completeNumber) {
        if (this->sign == 1)
            return (integerNum + 1) << pushNum;
        else
            return (integerNum * this->sign - 1) << pushNum;
    }
    if (this->sign == 1)
        return integerNum << pushNum;
    return (integerNum * this->sign) << pushNum;
}