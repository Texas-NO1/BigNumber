/*************************************************************************
	> File Name: rsa.h
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Sun 20 Dec 2020 04:39:57 PM CST
 ************************************************************************/

#ifndef _RSA_H
#define _RSA_H
#include <bignumber.h>
class RSA {
public:
    void get_key(string &, string &, string &);
    string encoding(const string &, const string &, const string &);
    string decoding(const string &, const string &, const string &);
private:
    BigNumber ex_gcd(BigNumber, BigNumber, BigNumber &, BigNumber &);
    BigNumber getn(const BigNumber &, const BigNumber &);
    BigNumber getfn(const BigNumber &, const BigNumber &);
    BigNumber gete(const BigNumber &);
    BigNumber getd(const BigNumber &);
    BigNumber square_and_multiply(const BigNumber &, const BigNumber &, const BigNumber &);
};
#endif
