/*************************************************************************
	> File Name: test.cpp
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Fri 18 Dec 2020 10:23:53 AM CST
 ************************************************************************/

#include <iostream>
#include <bignumber.h>
#include <cstdlib>
#include <ctime>
using namespace std;
#define P(a) {\
    cout << #a << "=" << a << endl;\
}
#define EQ(x, y, a, b) {\
    if (a != b) {\
        P(x) P(y)\
        P(a) P(b) \
        cout << "NO" << endl;\
    }\
}
int compare(long long x, long long y) {
    if (x == y) return 0;
    if (x < y) return -1;
    if (x > y) return 1;
}
void test1() {
    int n = 1000000;
    // ----------------------------------------------------
    // ----------------------------------------------------
    while (n--) {
        long long x = rand(), y = rand();
        string xx = "", yy = "";
        x = rand() % 2 ? x : (xx += '-', -x);
        y = rand() % 2 == 0 ? y : (yy += '-', -y);
        if (rand() % 1000 == 0) x = 0;
        if (rand() % 1000 == 1) y = 0;
        int za = rand() % 10, zb = rand() % 10;
        while (za--) xx += '0';
        while (zb--) yy += '0';
        xx += to_string(abs(x));
        yy += to_string(abs(y));
        BigNumber a = xx, b = yy;
        BigNumber s;
        string temp;
        int op = rand() % 11;
        switch (op) {
            case 0:
                s = a + b;
                EQ(x, y, s.value(), to_string(x + y))
                break;
            case 1:
                s = a - b;
                EQ(x, y, s.value(), to_string(x - y))
                break;
            case 2:
                s = a * b;
                EQ(x, y, s.value(), to_string(x * y))
                break;
            case 3:
                s = a / b;
                if (y == 0) {
                    EQ(x, y, s.value(), "0");
                    break;
                }
                EQ(x, y, s.value(), to_string(x / y))
                break;
            case 4:
                s = a % b;
                if (y == 0) {
                    EQ(x, y, s.value(), "0");
                    break;
                }
                EQ(x, y, s.value(), to_string(x % y))
                break;
            case 5:
                a += b;
                EQ(x, y, a.value(), to_string(x += y))
                break;
            case 6:
                a -= b;
                EQ(x, y, a.value(), to_string(x -= y))
                break;
            case 7:
                a *= b;
                EQ(x, y, a.value(), to_string(x *= y))
                break;
            case 8:
                a /= b;
                if (b == 0) {
                    EQ(x, y, a.value(), "0")
                    break;
                }
                EQ(x, y, a.value(), to_string(x /= y))
                break;
            case 9:
                a %= b;
                if (b == 0) {
                    EQ(x, y, a.value(), to_string(0))
                    break;
                }
                EQ(x, y, a.value(), to_string(x %= y))
                break;
            case 10:
                EQ(x, y, compare(x, y), a.compare(b))
                break;
        }
    }
}

int main() {
    srand(time(0));
    test1();
    return 0;
}
