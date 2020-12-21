/*************************************************************************
	> File Name: miller_rabin.cpp
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Mon 21 Dec 2020 02:35:34 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;
typedef unsigned long long ll;
#define MAX_NUM 25
int prime[MAX_NUM] = {
    3, 5, 7, 11, 13,
    17, 19, 23, 29, 31,
    37, 41, 43, 47, 53,
    59, 61, 67, 71, 73,
    79, 83, 89, 97, 101
};

ll ponyFE(ll a, ll b, ll c) {
    ll ans = 1;
    a %= c;
    while (b != 0) {
        if (b & 1) ans = (ans * a) % c;
        b >>= 1;
        a = (a * a) % c;
    }
    return ans;
}

bool miller_rabin(ll x, ll times) {
    if (x == 2) return true;
    if (!(x & 1) || x == 1) return false;
    bool pass;
    ll d = x - 1, m;
    while (!(d & 1)) d >>= 1;
    ll temp = d;
    for (int i = 1; i <= times; i++) {
        d = temp;
        pass = false;
        m = ponyFE(rand() % (x - 2) + 2, d, x);
        if (m == 1) continue;
        else {
            for (; d < x && d >= 0; m = (m * m) % x, d <<= 1) 
            if (m == x - 1) {
                pass = 1;
                break;
            }
        }
        if (!pass) return 0;
    }
    return 1;
}
ll pseudoprime(ll bits) {
    bool ifprime = false;
    ll num = 0;
    while (!ifprime)
    {
        num = 1;
        num <= 1;
        for (int i = 1; i < bits - 1; i++) {
            if (rand() & 1) num |= 1;
            num <<= 1;
        }
        num |= 1;
        ifprime = true;
        for (int j = 0; j< MAX_NUM; ++j)
        {
            if (num % prime[j] == 0)
            {
                ifprime = false;
                break;
            }
        }
    }
    return num;
}

ll rand_prime(ll bits, ll times) {
    ll ans;
    do {
        ans = pseudoprime(bits);
    } while (!miller_rabin(ans, times));
    return ans;
}
