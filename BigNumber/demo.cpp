/*************************************************************************
	> File Name: demo.cpp
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Mon 21 Dec 2020 09:35:51 AM CST
 ************************************************************************/

#include <iostream>
#include <bignumber.h>
using namespace std;
#define P(a, b, op) {\
    cout << #a << #op << #b << " = " << a op b << endl;\
}
int main() {
    BigNumber a, b;
    cout << "输入两个大整数" << endl;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    P(a, b, +)
    P(a, b, -)
    P(a, b, *)
    P(a, b, /)
    P(a, b, %)
    return 0;
}
