/*************************************************************************
	> File Name: rsa.cpp
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Fri 18 Dec 2020 09:44:41 AM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <ctime>
#include <BigNumber/bignumber.h>
#include <cstdlib>
#define MAX_N 10000
#define P(a){\
    cout << #a << "=" << a << endl;\
}
using namespace std;
typedef BigNumber big;
typedef long long ll;

int prime[MAX_N + 5];

void prime_init();
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
int main() {
    prime_init();
    srand(time(0));
    //int p =prime[rand() % prime[0] + 1], q = prime[rand() % prime[0] + 1];
    int len = 1024;
    big num = 1;
    for (int i = 0; i < len; i++) {
        cout << num << endl;
        num *= 2;
    }
    return 0;
    big p = 397, q = 401;
    big n = getn(p, q);
    big fn = getfn(p, q);
    big e = 343;
    big d = getd(e, fn);
    string str;
    big M,C;
    string s;
    while (true) {
        int op;
        cout << "choose operator: encode(1), decode(2), exit(0) : ";
        cin >> op;
        switch (op) {
            case 0:
                return 0;
            case 1:
                cout << "input target string : " << endl;
                cin >> M;
                C = encoding(M, e, n);
                cout << "eoncoding " << M <<" to " << C << endl;
                break;
            case 2:
                cout << "input source number : " << endl;
                cin >> C;
                M = decoding(C, d, n);
                cout << "decoding " << C << " to " << M << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
void prime_init() {
    for (int i = 2; i <= MAX_N; i++) {
        if (prime[i] == 0) {
            prime[++prime[0]] = i;
        }
        for (int j = 1; j <= prime[0] && i * prime[j] <= MAX_N; j++) {
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
big getn(big p, big q) {
    return p * q;
}
big getfn(big p, big q) {
    return (p - 1) * (q - 1);
}
big gete(big fn) {
    big x, y;
    for (big i = 2; i < fn; i = i + 1) {
        if (ex_gcd(i, fn, x, y) == 1) return i;
    }
    return -1;
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
big string_to_big(string s) {
    big ans = 1;
    for (int i = 0; i < s.size(); i++) {
        ans = ans * 100 + s[i] - 'A';
    }
    return ans;
}
string big_to_string(big x) {
    string ans = "";
    while (x > 1) {
        big temp = x % 100;
        x = x / 100;
        int val = stoi(temp.value());
        ans += val + 'A';
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

