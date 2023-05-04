#pragma once

#include <iostream>
#include <cmath>

template <typename T>
class ComplexNumber {
    T re_;
    T im_;

public:
    ComplexNumber(T re = 0, T im = 0) : re_(re), im_(im) {};

    friend std::ostream & operator << (std::ostream & str, const ComplexNumber & c) {
        if (c.re_ != 0 || c.im_ == 0) str << c.re_;
        if (c.re_ != 0 && c.im_ != 0) str << (c.im_ >= 0 ? " + " : " - ") << std::abs(c.im_) << "i";
        if (c.re_ == 0 && c.im_ != 0) str << c.im_ << "i";
        return str;
    }

    ComplexNumber operator + (const T & num) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ + num;
        result.im_ = this -> im_;
        return result;
    }
    ComplexNumber operator + (const ComplexNumber & other) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ + other.re_;
        result.im_ = this -> im_ + other.im_;
        return result;
    }
    // could add += support

    ComplexNumber operator - (const T & num) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ - num;
        result.im_ = this -> im_;
        return result;
    }
    ComplexNumber operator - (const ComplexNumber & other) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ - other.re_;
        result.im_ = this -> im_ - other.im_;
        return result;
    }
    // could add -= support

    ComplexNumber operator * (const T & num) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ * num;
        result.im_ = this -> im_ * num;
        return result;
    }
    ComplexNumber operator * (const ComplexNumber & other) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ * other.re_ - this -> im_ * other.im_;
        result.im_ = this -> re_ * other.im_ + this -> im_ * other.re_;
        return result;
    }
    // could add *= support

    ComplexNumber operator / (const T & num) {
        ComplexNumber<T> result;
        result.re_ = this -> re_ / num;
        result.im_ = this -> im_ / num;
        return result;
    }
    ComplexNumber operator / (const ComplexNumber & other) {
        ComplexNumber<T> result;
        ComplexNumber<T> conjugate(other.re_, -other.im_);
        T denominator;
        denominator = other.re_ * conjugate.re_ - other.im_ * conjugate.im_;
        result.re_ = (this -> re_ * conjugate.re_ - this -> im_ * conjugate.im_) / denominator;
        result.im_ = (this -> re_ * conjugate.im_ + this -> im_ * conjugate.re_) / denominator;
        return result;
    }
    // could add /= support
};
