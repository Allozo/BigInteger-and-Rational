#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

#include <sstream>
#include "biginteger.h"

class Rational {
public:
    Rational();
    Rational(int _numerator);
    Rational(int _numerator, int _denominator);
    Rational(BigInteger &_numerator, BigInteger &_denominator);
    //// внимательно посмотри сюда и задумайся о жизни
    explicit Rational(BigInteger value);
    Rational(const BigInteger &value);

    Rational &operator=(const Rational &other);

    string toString() const;
    friend  ostream &operator<<(ostream &, const Rational &);

    bool operator<(const Rational &other) const;
    bool operator>(const Rational &other) const;
    bool operator<=(const Rational &other) const;
    bool operator>=(const Rational &other) const;
    bool operator==(const Rational &other) const;
    bool operator!=(const Rational &other) const;

    friend bool operator<(const int &left_i, const Rational &right_r);
    friend bool operator>(const int &left_i, const Rational &right_r);
    friend bool operator<=(const int &left_i, const Rational &right_r);
    friend bool operator>=(const int &left_i, const Rational &right_r);
    friend bool operator==(const int &left_i, const Rational &right_r);
    friend bool operator!=(const int &left_i, const Rational &right_r);

    Rational operator-() const;
    Rational operator+() const;

    friend Rational operator+(const Rational &left_r, const Rational &right_r);
    friend Rational operator-(const Rational &left_r, const Rational &right_r);
    friend Rational operator*(const Rational &left_r, const Rational &right_r);
    friend Rational operator/(const Rational &left_r, const Rational &right_r);

    Rational &operator+=(const Rational &other);
    Rational &operator-=(const Rational &other);
    Rational &operator*=(const Rational &other);
    Rational &operator/=(const Rational &other);

    //  Increment/ decrement
    Rational &operator++();
    Rational &operator--();

    const Rational operator++(int);
    const Rational operator--(int);

    string asDecimal(size_t precision = 0) const;

    explicit operator double ();
    explicit operator bool();

    BigInteger getNumerator() const {
        return numerator;
    }

    BigInteger getDenominator() const {
        return denominator;
    }

private:
    BigInteger numerator;   // числитель
    BigInteger denominator; // знаменатель
    bool sign;

    // алгоритм Евклида
    static BigInteger NOD (const BigInteger &a, const BigInteger &b) {
        BigInteger _a = a;
        BigInteger _b = b;

        while (_a != 0 && _b != 0) {
            if (_a > _b) {
                _a %= _b;
            } else {
                _b %= _a;
            }
        }
        return _a + _b;
    }

    // приводит дробь к несократимой
    void check() {
        if (numerator == 0) {
            denominator = 1;
            sign = true;
            return;
        }
        BigInteger nod = 0;

        while (nod != 1) {
            nod = NOD(numerator, denominator);
            numerator /= nod;
            denominator /= nod;
        }
    }
};

Rational::Rational() {
    sign = true;
}
Rational::Rational(int _numerator) {
    sign = (_numerator >= 0);
    numerator = abs(_numerator);
    denominator = 1;
}
Rational::Rational(int _numerator, int _denominator) {
    if (_denominator == 0) {
//        cerr << "Деление на ноль!" << endl;
//        exit(123);
    }
    if (_numerator == 0) {
        sign = true;
    } else {
        sign = ((_numerator > 0)  == (_denominator > 0));
    }
    numerator = abs(_numerator);
    denominator = abs(_denominator);
    check();
}
Rational::Rational(BigInteger &_numerator, BigInteger &_denominator) {
    if (_denominator == 0) {
//        cerr << "Деление на ноль!" << endl;
//        exit(123);
    }
    if (_numerator == 0) {
        sign = true;
    } else {
        sign = ((_numerator > 0)  == (_denominator > 0));
    }
    numerator = _numerator.big_int_abs();
    denominator = _denominator.big_int_abs();
    check();
}
Rational::Rational(BigInteger value) {
    sign = (value >= 0);
    numerator = value.big_int_abs();
    denominator = 1;
}
Rational::Rational(const BigInteger &value) {
    sign = (value >= 0);
    numerator = value.big_int_abs();
    denominator = 1;
}

Rational &Rational::operator=(const Rational &other) {
    if (*this == other) {
        return *this;
    } else {
        this->sign = other.sign;
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }
}

string Rational::toString() const {
    string result;
    if (!sign) {
        result = "-";
    }
    result += numerator.toString();
    if (denominator != 1) {
        result += '/' + denominator.toString();
    }
    return result;
}
ostream &operator<<(ostream &str, const Rational &other) {
    str << other.toString();
    return str;
}

bool Rational::operator<(const Rational &other) const {
    return (other > *this);
}
bool Rational::operator>(const Rational &other) const {
    // + +
    if (this->sign && !other.sign) {
        return true;
        // - +
    } else if (!this->sign && other.sign) {
        return false;
        // + +
    } else if (this->sign && other.sign) {
        Rational left_rational = *this;
        Rational right_rational = other;

        // посчитаем числители при общем знаменателе
        left_rational.numerator *= right_rational.denominator;
        right_rational.numerator *= left_rational.denominator;

        return left_rational.numerator > right_rational.numerator;
        // - -
    } else {
        Rational left_rational = *this;
        Rational right_rational = other;

        left_rational.sign = true;
        right_rational.sign = true;

        return right_rational > left_rational;
    }
}
bool Rational::operator<=(const Rational &other) const {
    return (*this < other || *this == other);
}
bool Rational::operator>=(const Rational &other) const {
    return (*this > other || *this == other);
}
bool Rational::operator==(const Rational &other) const {
    return (this->sign == other.sign && this->numerator == other.numerator && this->denominator == other.denominator);
}
bool Rational::operator!=(const Rational &other) const {
    return !(*this == other);
}

bool operator<(const int &left_i, const Rational &right_r) {
    return right_r > left_i;
}
bool operator>(const int &left_i, const Rational &right_r) {
    return right_r < left_i;
}
bool operator<=(const int &left_i, const Rational &right_r) {
    return right_r >= left_i;
}
bool operator>=(const int &left_i, const Rational &right_r) {
    return right_r <= left_i;
}
bool operator==(const int &left_i, const Rational &right_r) {
    return right_r == left_i;
}
bool operator!=(const int &left_i, const Rational &right_r) {
    return right_r != left_i;
}

Rational Rational::operator-() const {
    Rational result = *this;
    result.sign = !this->sign;
    if (result.numerator == 0) {
        result.sign = true;
    }

    return result;
}
Rational Rational::operator+() const {
    return *this;
}

Rational operator+(const Rational &left_r, const Rational &right_r) {
    Rational result, left = left_r, right = right_r;

    // (+) + (+)
    if (left_r.sign && right_r.sign) {
        left.numerator *= right.denominator;
        right.numerator *= left.denominator;

        result.sign = true;
        result.numerator = left.numerator + right.numerator;
        result.denominator = left.denominator * right.denominator;

        // (+) + (-)
    } else if (left_r.sign && !right_r.sign) {
        // сведём к (+) - (+)
        right.sign = true;
        result = left - right;
        // (-) + (+)
    } else if (!left_r.sign && right_r.sign) {
        // сведём к (+) + (-)
        result = right + left;
        // (-) + (-)
    } else if (!left_r.sign && !right_r.sign) {
        // сведём к -((+) + (+))
        left.sign = true;
        right.sign = true;
        result = left + right;
        result.sign = false;
    }

    result.check(); // проверим на несократимость
    return  result;
}
Rational operator-(const Rational &left_r, const Rational &right_r) {
    Rational result, left = left_r, right = right_r;

    // (+) - (+)
    if (left_r.sign && right_r.sign) {
        // домножаем числители на знаменатели
        left.numerator *= right.denominator;
        right.numerator *= left.denominator;

        result.numerator = left.numerator - right.numerator;
        result.denominator = left.denominator * right.denominator;

        // в числителе может быть минус, нужно вынести его перед дробью
        result.sign = result.numerator.sign;
        result.numerator.sign = true;
        // (+) - (-)
    } else if (left_r.sign && !right_r.sign) {
        // сведём к (+) + (+)
        right.sign = true;
        result = left + right;
        // (-) - (+)
    } else if (!left_r.sign && right_r.sign) {
        // сведём к (-) + (-)
        right.sign = false;
        result = left + right;

        // (-) - (-)
    } else if (!left_r.sign && !right_r.sign) {
        // сведём к (-) + (+)
        right.sign = true;
        result = left + right;
    }

    result.check(); // проверим на несократимость
    return  result;
}
Rational operator*(const Rational &left_r, const Rational &right_r) {
    Rational result;

    result.numerator = left_r.numerator * right_r.numerator;
    result.denominator = left_r.denominator * right_r.denominator;

    result.sign = (left_r.sign == right_r.sign);

    result.check();
    return result;
}
Rational operator/(const Rational &left_r, const Rational &right_r) {
    Rational result;

    if (right_r.numerator == 0) {
//        cerr << "Деление на 0" << endl;
//        exit(123);
    }

    result.numerator = left_r.numerator * right_r.denominator;
    result.denominator = left_r.denominator * right_r.numerator;

    result.sign = (left_r.sign == right_r.sign);

    result.check();
    return result;
}

Rational &Rational::operator+=(const Rational &other) {
    *this = *this + other;
    return *this;
}
Rational &Rational::operator-=(const Rational &other) {
    *this = *this - other;
    return *this;
}
Rational &Rational::operator*=(const Rational &other) {
    *this = *this * other;
    return *this;
}
Rational &Rational::operator/=(const Rational &other) {
    *this = *this / other;
    return *this;
}

Rational &Rational::operator++() {
    *this += 1;
    return *this;
}
Rational &Rational::operator--() {
    *this -= 1;
    return *this;
}

const Rational Rational::operator++(int) {
    Rational res = *this;
    ++(*this);
    return res;
}
const Rational Rational::operator--(int) {
    Rational res = *this;
    --(*this);
    return res;
}

string Rational::asDecimal(size_t precision) const {
    if (this->numerator == 0) {
        string result = "0";
        return result;
    }

    Rational value = *this;

    for (size_t i = 0; i < precision; i++) {
        value.numerator *= 10;
    }
    BigInteger r = value.numerator / value.denominator;

    ostringstream stream;
    stream << r;
    string result = stream.str();


    if (precision > 0) {
        size_t n = result.size();
        if (precision > result.size()) {
            for (size_t i = 0; i < precision - n ; i++) {
                result.insert(0, "0");
            }
        }
        result.insert(result.size() - precision, ".");
    }

    // учтем, если дробь меньше 1
    if (this->numerator < this->denominator && precision > 0) {
        result.insert(0, "0");
    }

    // учтем знак дроби
    if (!this->sign && r != 0) {
        result.insert(0, "-");
    }

    //// Нужно ли убирать бесполезные нули после запятой?
    if (precision > 0) {
        while (result[result.size() - 1] == '0' && result[result.size() - 2] != '.') {
            result.pop_back();
        }
    }

    return result;
}

Rational::operator double() {
    string value = this->asDecimal(8);
    double d = 0.0;
    stringstream ss(value);
    ss >> d;
    return d;
}

Rational::operator bool() {
    return *this != 0;
}

#endif
