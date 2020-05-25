#include <iostream>
#include <random>
#include "rational.h"

using namespace std;

class RationalDivisionByZero {
};



void test() {
    int a1, a2;
    cin >> a1 >> a2;
    Rational r1(a1, a2), r2(5);
    cout << r1 << endl;
    cout << r1 << " < " << r2 << " == " << (r1 < r2) << endl;
    cout << r1 << " > " << r2 << " == " << (r1 > r2) << endl;
    cout << r1 << " <= " << r2 << " == " << (r1 <= r2) << endl;
    cout << r1 << " >= " << r2 << " == " << (r1 >= r2) << endl;
    cout << r1 << " == " << r2 << " == " << (r1 == r2) << endl;
    cout << r1 << " != " << r2 << " == " << (r1 != r2) << endl;

    cout << endl;

    cout << r1 << " + " << r2 << " == " << (r1 + r2) << endl;
    cout << r1 << " - " << r2 << " == " << (r1 - r2) << endl;
    cout << r1 << " * " << r2 << " == " << (r1 * r2) << endl;
    cout << r1 << " / " << r2 << " == " << (r1 / r2) << endl;

    cout << endl;

    Rational r3;
    r3 = r1; r3 += r2;
    cout << r1 << " += " << r2 << " == " << r3 << endl;
    r3 = r1; r3 -= r2;
    cout << r1 << " -= " << r2 << " == " << r3 << endl;
    r3 = r1; r3 *= r2;
    cout << r1 << " *= " << r2 << " == " << r3 << endl;
    r3 = r1; r3 /= r2;
    cout << r1 << " /= " << r2 << " == " << r3 << endl;

    cout << endl;

    cout << "Округление " << r1 << " до целого == " << r1.asDecimal() << endl;
    cout << "Округление " << r1 << " до 7 знаков == " << r1.asDecimal(7) << endl;
    cout << "double r3 == " << r1 << " == " << (double) r1 << endl;

    Rational rr(5);
    BigInteger bb(3);
    cout << bb + rr << endl;
    cout << BigInteger(3) + Rational(5) << endl;
    cout << Rational(5) + BigInteger(3) << endl;
}

void test_1() {
    int a = 3;
//    cin >> a;

    int p = -9, q = -3;
//    cin >> p >> q;
    const Rational rc(p, q); // q != 0 is guaranteed by author of tests
    cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

    Rational r1(-5, 6), r2(0);
//    cin >> r1 >> r2;

    cout << r1 << endl;
    cout << r2 << endl;

    try {
        cout << 1 / r1 << endl;
    } catch (const RationalDivisionByZero& ex) {
        cout << "Cannot get reciprocal of r1." << endl;
    }

    try {
        cout << rc / r2 << endl;
    } catch (const RationalDivisionByZero& ex) {
        cout << "Cannot divide by r2." << endl;
    }

    cout << (r1 < r2) << endl;
    cout << (r1 <= r2) << endl;
    cout << (r1 > r2) << endl;
    cout << (r1 >= r2) << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 != r2) << endl;

    cout << (r1 < a) << endl;
    cout << (r1 <= a) << endl;
    cout << (r1 > a) << endl;
    cout << (r1 >= a) << endl;
    cout << (r1 == a) << endl;
    cout << (r1 != a) << endl << endl;

    cout << (a < r2) << endl;
    cout << (a <= r2) << endl;
    cout << (a > r2) << endl;
    cout << (a >= r2) << endl;
    cout << (a == r2) << endl;
    cout << (a != r2) << endl << endl;

    cout << rc + a << endl
         << a + rc << endl
         << -rc * r1 << endl
         << (+r1 - r2 * rc) * a << endl;

    cout << ++r1 << endl;
    cout << r1 << endl;
    cout << r1++ << endl;
    cout << r1 << endl;
    cout << --r1 << endl;
    cout << r1 << endl;
    cout << r1-- << endl;
    cout << r1 << endl;
    cout << ++++r1 << endl;
    cout << r1 << endl;

    cout << ((((r1 += r2) /= Rational(-5,3)) -= rc) *= a) << endl;
    cout << (r1 += r2 /= 3) << endl;
    cout << r1 << endl;
    cout << r2 << endl;
}

void test_2() {
    Rational a(1, 1),
    b(-1, 1),
    c(1, 40),
    r;
    r = a*b*c;
    cout << a*b*c << endl;
    cout << r.asDecimal(5) << endl;
}

void stress_test() {
    default_random_engine dre;
    std::uniform_int_distribution<int> di(-2000000000,2000000000);


    for (int i = 0; i < 10000; i++) {
        int a_int = di(dre);
        int b_int = di(dre);
        int c_int = di(dre);
        int d_int = di(dre);

        Rational int_a(a_int, b_int);
        Rational int_b(c_int, d_int);

        double a = (double)(a_int) / (double)(b_int);
        double b = (double)(c_int) / (double)(d_int);

        Rational int_a_plus_b = int_a + int_b;
        Rational int_a_minus_b = int_a - int_b;
        Rational int_a_mul_b = int_a * int_b;
        Rational int_a_del_b = int_a / int_b;

        if (((double)int_a_plus_b - (a + b)) >= 0.0000001) {
            cout << "--------------------------------------" << endl;
            cout << "operation -> + " << endl;
            cout << "a == " << a << " int_a = "; cout << (double)int_a << endl;
            cout << "b == " << b << " int_b = "; cout << (double)int_b << endl;
            cout << "a + b         == " << a + b << endl;
            cout << "int_a + int_b == ";
            cout << (double)int_a_plus_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (((double)int_a_minus_b - (a - b)) >= 0.0000001) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> - " << endl;
            cout << "a == " << a << " int_a = ";
            cout << (double)int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << (double)int_b << endl;
            cout << "a - b         == " << a - b << endl;
            cout << "int_a - int_b == ";
            cout << (double)int_a_minus_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (((double)int_a_mul_b - a * b) >= 0.0000001) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> * " << endl;
            cout << "a == " << a << " int_a = ";
            cout << (double)int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << (double)int_b << endl;
            cout << "a * b         == " << a * b << endl;
            cout << "int_a * int_b == ";
            cout << (double)int_a_mul_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (((double)int_a_del_b - a / b) >= 0.0000001) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> / " << endl;
            cout << "a == " << a << " int_a = ";
            cout << (double)int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << (double)int_b << endl;
            cout << "a / b         == " << a / b << endl;
            cout << "int_a / int_b == ";
            cout << (double)int_a_del_b << endl;
            cout << "--------------------------------------" << endl;
        }
    }
}

void test4() {
    Rational s = 4*3*7*13*19*41*43*11;
    Rational t = s - 25;
    ((s = 1000000007) *= 1000000009) *= 2147483647;
    if ((s/t).asDecimal(10) != "5337140829307966068.3989202202") std::cout << "Error 7" << std::endl;
}

void test_biginteger() {
    long long g = 1000000000;
    srand(time(nullptr));
    string s = "0";
    BigInteger bi(s);
    bi -= 990;
    cout << bi << endl;


    for (int i = 0; i < 100; i++) {
        long long b = rand() % g - 500000000;
        long long a = rand() % g - 500000000;
//        cin >> a;
//        cin >> b;

        BigInteger int_a = a;
        BigInteger int_b = b;

//        cout << a << " " << b;
        BigInteger int_a_plus_b = int_a + int_b;
        BigInteger int_a_minus_b = int_a - int_b;
        BigInteger int_a_mul_b = int_a * int_b;
        BigInteger int_a_del_b = int_a / int_b;
        BigInteger int_a_mod_b = int_a % int_b;

        if (!(int_a_plus_b == a + b)) {
            cout << "--------------------------------------" << endl;
            cout << "operation -> + " << endl;
            cout << "a == " << a << " int_a = ";
            cout << int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << int_b << endl;
            cout << "a + b         == " << a + b << endl;
            cout << "int_a + int_b == ";
            cout << int_a_plus_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (!(int_a_minus_b == a - b)) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> - " << endl;
            cout << "a == " << a << " int_a = ";
            cout << int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << int_b << endl;
            cout << "a - b         == " << a - b << endl;
            cout << "int_a - int_b == ";
            cout << int_a_minus_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (!(int_a_mul_b == a * b)) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> * " << endl;
            cout << "a == " << a << " int_a = ";
            cout << int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << int_b << endl;
            cout << "a * b         == " << a * b << endl;
            cout << "int_a * int_b == ";
            cout << int_a_mul_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (!(int_a_del_b == a / b)) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> / " << endl;
            cout << "a == " << a << " int_a = ";
            cout << int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << int_b << endl;
            cout << "a / b         == " << a / b << endl;
            cout << "int_a / int_b == ";
            cout << int_a_del_b << endl;
            cout << "--------------------------------------" << endl;
        }
        if (!(int_a_mod_b == a % b)) {
            cout << "--------------------------------------" << endl;
            cout << "operation-> % " << endl;
            cout << "a == " << a << " int_a = ";
            cout << int_a << endl;
            cout << "b == " << b << " int_b = ";
            cout << int_b << endl;
            cout << "a % b         == " << a % b << endl;
            cout << "int_a % int_b == ";
            cout << int_a_mod_b << endl;
            cout << "--------------------------------------" << endl;
        }

    }
}

int main() {
//    test();
//    test_1();
    test_2();
//    stress_test();
//    test4();
//    test_biginteger();
    return 0;
}
