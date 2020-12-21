/*************************************************************************
	> File Name: rsa.cpp
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Fri 18 Dec 2020 09:44:41 AM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <ctime>
#include "BigNumber/bignumber.h"
#include "RandPrime/rand_prime.h"
#include <cstdlib>
using namespace std;
typedef BigNumber big;

big ex_gcd(big, big, big &, big &);
big getn(big, big);
big getfn(big, big);
big gete(big);
big getd(big, big);
big square_and_multiply(big, big, big);
big encoding(big, big, big);
big decoding(big, big, big);
big string_to_big(string);
string big_to_string(big);
int main() {
    srand(time(0));
    big p = rand_prime(34, 10);
    big q = rand_prime(33, 10);
    big n = getn(p, q);
    big fn = getfn(p, q);
    big e = gete(fn);
    big d = getd(e, fn);
    cout << "Public Key: (e, n) = (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (d, n) = (" << d << ", " << n << ")" << endl;
    while (true) {
        char op;
        string str;
        big C;
        cout << "选择操作:(1)加密,(2)解密,(0)退出: ";
        cin >> op;
        switch (op) {
            case '1':
                cout << "输入待加密字符串(最长" << (n.length() - 1) / 2 << ")：";
                cin >> str;
                cout << "加密后的秘文: " << encoding(string_to_big(str), e, n) << endl;
                break;
            case '2':
                cout << "输入秘文: ";
                cin >> C;
                cout << "解密后得字符串: " << big_to_string(decoding(C, d, n)) << endl;
                break;
            default: return 0;
        }
    }
    return 0;
}

big getn(big p, big q) {
    return p * q;
}

big getfn(big p, big q) {
    return (p - 1) * (q - 1);
}

big gete(big fn) {
    return 65537;
}

big getd(big e, big fn) {
    big x, y;
    ex_gcd(e, fn, x, y);
    return (x + fn) % fn;
}

big square_and_multiply(big a, big x, big n) {
    big y = 1;
    for (int i = 0; x > 0; i++) {
        if (x.isodd()) y = (a * y) % n;
        a = (a * a) % n;
        x = x / 2;
    }
    return y;
}

big encoding(big M, big e, big n) {
    return square_and_multiply(M, e, n);
}

big decoding(big C, big d, big n) {
    return square_and_multiply(C, d, n);
}

int char_int(char x) {
    char int0 = 10, intA = 20, inta = 50;
    if (x >= '0' && x <= '9') return x - '0' + int0;
    if (x >= 'A' && x <= 'Z') return x - 'A' + intA;
    if (x >= 'a' && x <= 'z') return x - 'a' + inta;
    return 0;
}

char int_char(int x) {
    if (x >= 50) return x - 50 + 'a';
    if (x >= 20) return x - 20 + 'A';
    if (x >= 10) return x - 10 + '0';
    return 0;
}

big string_to_big(string s) {
    big ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans = ans * 100 + char_int(s[i]);
    }
    return ans;
}

string big_to_string(big x) {
    string ans = "";
    while (x > 1) {
        big temp = x % 100;
        x = x / 100;
        int t = stoi(temp.value());
        ans += int_char(t);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

big ex_gcd(big a, big b, big &x, big &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    big ans = ex_gcd(b, a % b, x, y);
    big xx = x, yy = y;
    x = yy;
    y = xx - (a / b) * yy;
    return ans;
}
