#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

//  основание системы
const int now_radix = 10;

class BigInteger {
public:
/*
 * Конструкторы
 */
    BigInteger();                                                        // работает
    BigInteger(long long value);                                         // работает
    BigInteger(string &value);                                           // работает
    BigInteger(long long value, int new_radix);


    BigInteger &operator=(const BigInteger &other) {
        if (*this == other) {
            return *this;
        } else {
            this->sign = other.sign;
            this->number = other.number;
            this->radix = other.radix;
            return *this;
        }
    }                 // работает

/*
 * Логические операции
 */
    bool operator<(const BigInteger &other) const;                       // работает
    bool operator>(const BigInteger &other) const;                       // работает
    bool operator<=(const BigInteger &other) const;                      // работает
    bool operator>=(const BigInteger &other) const;                      // работает
    bool operator==(const BigInteger &other) const;                      // работает
    bool operator!=(const BigInteger &other) const;                      // работает

/*
 * арифметические операции
 */
    friend BigInteger operator+(const BigInteger &left_int, const BigInteger &right_int);
    friend BigInteger operator-(const BigInteger &left_int, const BigInteger &right_int);
    friend BigInteger operator*(const BigInteger &left_int, const BigInteger &right_int);
    friend BigInteger operator/(const BigInteger &left_int, const BigInteger &right_int);
    friend BigInteger operator%(const BigInteger &left_int, const BigInteger &right_int);

    BigInteger &operator+=(const BigInteger &other);
    BigInteger &operator-=(const BigInteger &other);
    BigInteger &operator*=(const BigInteger &other);
    BigInteger &operator/=(const BigInteger &other);
    BigInteger &operator%=(const BigInteger &other);

    //     Increment/ decrement
    BigInteger &operator++();
    BigInteger &operator--();

    const BigInteger operator++(int);
    const BigInteger operator--(int);


    //    Ввод / вывод
    string toString() const;

    friend istream &operator>>(istream &, BigInteger &);
    friend ostream &operator<<(ostream &, const BigInteger &);

    explicit operator bool();
    const BigInteger operator-();


//private:
    BigInteger big_int_abs() const;                                      // работает
    BigInteger &check_radix();
    BigInteger div_on_2();                                              // работает

    bool sign;
    vector<int> number;
    // основание системы счисления
    int radix = now_radix;
};

BigInteger::BigInteger() {
    sign = true;
}                                           // работает
BigInteger::BigInteger(long long value) {
    if (value == 0) {
        sign = true;
        number.push_back(0);
        return;
    }
    sign = (value > 0);
    value = abs(value);
    while (value > 0) {
        number.push_back(value % radix);
        value /= radix;
    }
}                            // работает
BigInteger::BigInteger(long long value, int new_radix) {
    radix = new_radix;
    if (value == 0) {
        sign = true;
        number.push_back(0);
        return;
    }
    sign = (value > 0);
    value = abs(value);
    while (value > 0) {
        number.push_back(value % radix);
        value /= radix;
    }
}
BigInteger::BigInteger(string &value) {
    if ((value == "0") || (value == "-") || (value == "-0") || (value == "")) {
        sign = true;
        number.push_back(0);
        return;
    }
    if (value[0] == '-') {
        sign = false;
        for (long i = value.size() - 1; i >= 1; i--) {
            number.push_back(value[i] - '0');
        }
    } else {
        sign = true;
        for (long i = value.size() - 1; i >= 0; i--) {
            number.push_back(value[i] - '0');
        }
    }
    check_radix();
}                              // работает


bool BigInteger::operator<(const BigInteger &other) const {
    return other > *this;
}          // работает
bool BigInteger::operator>(const BigInteger &other) const {
    if (this->sign && other.sign) {
//            оба положительные
        if (this->number.size() > other.number.size()) {
            return true;
        } else if (this->number.size() < other.number.size()) {
            return false;
        } else {
            for (long i = other.number.size() - 1; i >= 0; i--) {
                if (this->number[i] > other.number[i]) {
                    return true;
                } else if (this->number[i] < other.number[i]) {
                    return false;
                }
            }
//            числа равны => не "больше"
            return false;
        }
    } else if (!this->sign && other.sign) {
//            левый отрицательный, а правый положительный
        return false;
    } else if (this->sign && !other.sign) {
//            левый положительный, а правый отрицательный
        return true;
    } else if (!this->sign && !other.sign) {
//            оба отрицательные
        BigInteger this_int = *this;
        this_int.sign = true;
        BigInteger int_other = other;
        int_other.sign = true;
//        сравним модули этих чисел
        bool res = int_other > this_int;
        return res;
    }
    //// что это?
    return false;
}          // работает
bool BigInteger::operator<=(const BigInteger &other) const {
    return (*this < other or other == *this);
}         // работает
bool BigInteger::operator>=(const BigInteger &other) const {
    return (*this > other or other == *this);
}         // работает
bool BigInteger::operator==(const BigInteger &other) const {
    return (this->number == other.number and this->sign == other.sign);
}         // работает
bool BigInteger::operator!=(const BigInteger &other) const {
    return not(*this == other);
}         // работает

BigInteger operator+(const BigInteger &left_int, const BigInteger &right_int) {
    BigInteger res = left_int;
    res += right_int;
    return res;
}
BigInteger operator-(const BigInteger &left_int, const BigInteger &right_int) {
    BigInteger res = left_int;
    res -= right_int;
    return res;
}
BigInteger operator*(const BigInteger &left_int, const BigInteger &right_int) {
    BigInteger res = left_int;
    res *= right_int;
    return res;
}
BigInteger operator/(const BigInteger &left_int, const BigInteger &right_int) {
    BigInteger res = left_int;
    res /= right_int;
    return res;
}
BigInteger operator%(const BigInteger &left_int, const BigInteger &right_int) {
    BigInteger res = left_int;
    res %= right_int;
    return res;
}

BigInteger &BigInteger::operator+=(const BigInteger &other) {  // this += other
    if (this->sign && other.sign) { // если 2 положительных числа
        if (this->number.size() >= other.number.size()) {
            for (size_t i = 0; i < other.number.size(); i++) {
                this->number[i] += other.number[i];
            }
        } else if (this->number.size() < other.number.size()) {
            BigInteger c(0, this->radix);       // создаем пустую переменную
            c = other;          // записываем в неё other
            c += *this;         // к ней прибавляем this, это можно делать, так как длинна чисел: c > this
            *this = c;          //
        }
    } else if (this->sign && not other.sign) {
        BigInteger int_1 = other;
        int_1.sign = true;
        *this -= int_1;
    } else if (not this->sign && other.sign) {
        BigInteger int_this_abs = *this;
        int_this_abs.sign = true;

        if (int_this_abs >= other) {
            int_this_abs -= other;
            *this = int_this_abs;
            this->sign = false;
        } else {
            BigInteger res(0, this->radix);
            res = other;
            res += *this; // + *this;
            *this = res;
        }
    } else {
        BigInteger res;
        BigInteger int_1 = *this;
        int_1.sign = true;
        BigInteger int_2 = other;
        int_2.sign = true;
        res = int_1 + int_2;
        res.sign = false;
        *this = res;
    }
    check_radix();
    return *this;
}        // работает
BigInteger &BigInteger::operator-=(const BigInteger &other) {
    if (this->sign && other.sign) { // если 2 положительных числа
        BigInteger this_int = *this;
        if (this_int >= other) {
            if (this->number.size() >= other.number.size()) {
                for (size_t i = 0; i < other.number.size(); i++) {
                    this->number[i] -= other.number[i];
                }
            } else if (this->number.size() < other.number.size()) {
                BigInteger c;
                c = other;
                for (size_t i = 0; i < this->number.size(); i++) {
                    c.number[i] -= this->number[i];
                }
                *this = c;
            }
        } else {
            BigInteger res = other;
            res -= *this;
            res.sign = false;
            *this = res;
        }
    } else if (this->sign && not other.sign) {
        BigInteger int_1 = other;
        int_1.sign = true;
        *this += int_1;
    } else if (not this->sign && other.sign) {
        BigInteger int_1 = other;
        int_1.sign = false;
        *this += int_1;
        this->sign = false;
    } else {
        BigInteger int_1 = other;
        int_1.sign = true;
        *this += int_1;
    }
    check_radix();
    return *this;

}        // работает
BigInteger &BigInteger::operator*=(const BigInteger &other) {
    BigInteger res(0, this->radix);
    res.sign = this->sign == other.sign;
    res.number.resize(2 * (this->number.size() + other.number.size()) + 1);
    BigInteger this_now = *this;
    BigInteger other_now = other;

    if (max(other_now.number.size(), this_now.number.size()) < 4) {        // если меньше 3 разрядов, то наивно умножаем
        res.sign = this->sign == other_now.sign;
        size_t length = this->number.size() + other_now.number.size() + 1;
        res.number.resize(length, 0);

        for (size_t i = 0; i < this->number.size(); i++) {
            for (size_t j = 0; j < other_now.number.size(); j++) {
                res.number[i + j] += this->number[i] * other_now.number[j];
            }
        }

        res.check_radix();
        *this = res;

    } else {
        while (this_now.number.size() != other_now.number.size()) {
            if (this_now.number.size() < other_now.number.size()) {
                this_now.number.insert(this_now.number.end(), 0);
            }
            if (other_now.number.size() < this_now.number.size()) {
                other_now.number.insert(other_now.number.end(), 0);
            }
        }
        BigInteger a_1 = this_now;
        while (a_1.number.size() > this_now.number.size() / 2) {
            a_1.number.erase(a_1.number.begin());
        }
        BigInteger a_0 = this_now;    //  старшая часть числа this
        while (a_0.number.size() + a_1.number.size() != this_now.number.size()) {
            a_0.number.pop_back();
        }

        BigInteger b_1 = other_now;
        while (b_1.number.size() > other_now.number.size() / 2) {
            b_1.number.erase(b_1.number.begin());
        }
        BigInteger b_0 = other_now;    //  старшая часть числа other
        while (b_0.number.size() + b_1.number.size() != other_now.number.size()) {
            b_0.number.pop_back();
        }

        BigInteger sum_of_a_parts = a_0 + a_1;                 //
        BigInteger sum_of_b_parts = b_0 + b_1;
        BigInteger product_of_sums_of_parts = sum_of_a_parts * sum_of_b_parts;

        BigInteger product_of_first_parts = a_0 * b_0;
        BigInteger product_of_second_parts = a_1 * b_1;
        BigInteger sum_middle_terms = product_of_sums_of_parts - product_of_first_parts - product_of_second_parts;

        BigInteger first = product_of_first_parts;
        for (unsigned long i = 0; i < first.number.size(); i++) {
            res.number[i] += first.number[i];
        }
        BigInteger second = sum_middle_terms;
        for (unsigned long i = 0; i < second.number.size(); i++) {
            res.number[i + a_0.number.size()] += second.number[i];
        }
        BigInteger third = product_of_second_parts;
        for (unsigned long i = 0; i < third.number.size(); i++) {
            res.number[i + 2 * a_0.number.size()] += third.number[i];
        }

        res.check_radix();
        *this = res;
    }


    return *this;
}        // работает
BigInteger &BigInteger::operator/=(const BigInteger &other) {
    if (other == (BigInteger) 0) {
//        cout << "деление на 0" << endl;
        exit(123);
    }
    BigInteger first_abs_b = other.big_int_abs();
    BigInteger abs_this = this->big_int_abs();
    BigInteger r = this->big_int_abs();
    BigInteger l = 0;
    BigInteger mid;
    BigInteger last_mid;
    while (l <= r) {
        mid = l + r;
        mid = mid.div_on_2();
        if (mid * first_abs_b > abs_this) {
            r = mid - 1;
        } else {
            l = mid + 1;
            last_mid = mid;
        }
    }
    last_mid.sign = this->sign == other.sign;
    *this = last_mid;
    this->check_radix();
    return *this;
}        // работает
BigInteger &BigInteger::operator%=(const BigInteger &other) {
    BigInteger a = *this;
    BigInteger b = other;
    BigInteger c = a / b;
    BigInteger res = a - c * b;
    *this = res;
    this->check_radix();
    return *this;
}        // работает

BigInteger &BigInteger::operator++() {
    *this += 1;
    return *this;
}
BigInteger &BigInteger::operator--() {
    *this -= 1;
    return *this;
}

const BigInteger BigInteger::operator++(int) {
    BigInteger res = *this;
    ++(*this);
    return res;
}
const BigInteger BigInteger::operator--(int) {
    BigInteger res = *this;
    --(*this);
    return res;
}

string BigInteger::toString() const {
    string res;
    if (sign) {
        res = "";
    } else {
        res = "-";
    }
    if (number[0] == 0 and number.size() == 1) {
        res += "0";
        return res;
    }


    if (radix == 10) {
        for (long i = number.size() - 1; i >= 0; i--) {
            res.push_back(number[i] + '0');
        }
    } else {
        BigInteger res_int(0, 10);
        res_int.sign = sign;
        for (size_t i = 0; i < number.size(); i++) {
            BigInteger f(number[i], 10);
            for (size_t j = 0; j < i; j++) {
                BigInteger c(radix, 10);
                f *= c;
            }
            res_int += f;
        }
        res += res_int.toString();
    }
    return res;
}

istream &operator>>(istream &str, BigInteger &value) {
    string s;
    str >> s;
    BigInteger b(s);
    b.check_radix();
    value = b;
    return str;
}
ostream &operator<<(ostream &str, const BigInteger &other) {
    string s;
    s = other.toString();
    str << s;
    return str;
}

BigInteger::operator bool() {
    return *this != 0;
}
const BigInteger BigInteger::operator-() {
    BigInteger b = *this;
    b.sign = !this->sign;
    if (number.size() == 1 && number[0] == 0) {
        b.sign = true;
        b.number[0] = 0;
    }
    return b;
}

// работает
BigInteger BigInteger::big_int_abs() const {
    BigInteger res = *this;
    res.sign = true;
    return res;
}                         // работает
BigInteger &BigInteger::check_radix() {
    size_t i = 0;
//    числа в векторе < основания
    while (i < number.size()) {
        while (number[i] >= radix) {
            number[i] -= radix;
            if (i + 1 >= number.size()) {
                number.push_back(1);
            } else {
                number[i + 1]++;
            }
        }
        i++;
    }

    for (size_t k = 0; k < number.size(); k++) {
        if (number[k] < 0) {
            number[k] += radix;
            if (k + 1 >= number.size()) {
                sign = false;
            } else {
                number[k + 1]--;
            }
        }
    }

    i = 1;
    if (number[number.size() - i] == 0) {
//            если у числа есть нули в начале
        while (number[number.size() - i] == 0 and number.size() - i > 0) {
            i++;
        }
        vector<int> new_number(number.size() - i + 1);
        for (size_t j = 0; j < new_number.size(); j++) {
            new_number[j] = number[j];
        }
        number = new_number;
    }

//        проверка на -0
    if (number[0] == 0 and number.size() == 1) {
        sign = true;
    }

    return *this;
}
BigInteger BigInteger::div_on_2() {
    size_t carry = 0;
    long long i = number.size() - 1;
    while (i >= 0) {
        int cur = number[i] + carry * radix;
        number[i] = cur / 2;
        carry = cur % 2;
        i--;
    }
    check_radix();
    return *this;
}                                 // работает