#include <string>
#include <algorithm>
#include <cstdio>
#include <bignumber.h>
#define COLOR(a, b) "\033[0;" #b "m" a "\033[0m"
#define RED(a) COLOR(a, 31)
#define WARNING(format, message...) {\
    printf(RED("waring: "));\
    printf(format,##message);\
}
using namespace std;
BigNumber::BigNumber():data("0"),sign(0){}
BigNumber::BigNumber(const string &val):data(val){filter();judge();}
BigNumber::BigNumber(const BigNumber &b):data(b.data),sign(b.sign){}
BigNumber::BigNumber(const long long val):data(to_string(val)){filter();}
BigNumber::BigNumber(int news, const string &val):sign(news),data(val){}
bool BigNumber::operator<(const BigNumber &b) {
    return compare(b) < 0;
}
bool BigNumber::operator<=(const BigNumber &b) {
    return compare(b) <= 0;
}
bool BigNumber::operator>(const BigNumber &b) {
    return compare(b) > 0;
}
bool BigNumber::operator>=(const BigNumber &b) {
    return compare(b) >= 0;
}
bool BigNumber::operator==(const BigNumber &b) {
    return compare(b) == 0;
}
bool BigNumber::operator!=(const BigNumber &b) {
    return compare(b) != 0;
}
int BigNumber::compare(const BigNumber& b) {
    return compare(sign, data, b.sign, b.data);
}
BigNumber BigNumber::operator+(const BigNumber &big) {
    int c_sign;
    string c_data;
    calculate('+', sign, data, big.sign, big.data, c_sign, c_data);
    return BigNumber(c_sign, c_data);
}
BigNumber BigNumber::operator-(const BigNumber &big) {
    int c_sign;
    string c_data;
    calculate('-', sign, data, big.sign, big.data, c_sign, c_data);
    return BigNumber(c_sign, c_data);
}
BigNumber BigNumber::operator*(const BigNumber &big) {
    int c_sign;
    string c_data;
    calculate('*', sign, data, big.sign, big.data, c_sign, c_data);
    return BigNumber(c_sign, c_data);
}
BigNumber BigNumber::operator/(const BigNumber &big) {
    int c_sign;
    string c_data;
    calculate('/', sign, data, big.sign, big.data, c_sign, c_data);
    return BigNumber(c_sign, c_data);
}
BigNumber BigNumber::operator%(const BigNumber &big) {
    int c_sign;
    string c_data;
    calculate('%', sign, data, big.sign, big.data, c_sign, c_data);
    return BigNumber(c_sign, c_data);
}
BigNumber& BigNumber::operator+=(const BigNumber &big) { 
    calculate('+', sign, data, big.sign, big.data, sign, data);
    return *this;
}
BigNumber& BigNumber::operator-=(const BigNumber &big) {
    calculate('-', sign, data, big.sign, big.data, sign, data);
    return *this;
}
BigNumber& BigNumber::operator*=(const BigNumber &big) {
    calculate('*', sign, data, big.sign, big.data, sign, data);
    return *this;
}
BigNumber& BigNumber::operator/=(const BigNumber &big) {
    calculate('/', sign, data, big.sign, big.data, sign, data);
    return *this;
}
BigNumber& BigNumber::operator%=(const BigNumber &big) {
    calculate('%', sign, data, big.sign, big.data, sign, data);
    return *this;
}
string BigNumber::value() const {
    string res = (sign == 0) ? "" : "-";
    return res + data;
}
int BigNumber::length() const {
    return data.length();
}
bool BigNumber::isodd() const {
    return (data[data.length() - 1] - '0') % 2 == 1;
}
istream& operator>>(istream& in, BigNumber& big) {
    in >> big.data;
    big.filter();
    big.judge();
    return in;
}
ostream& operator<<(ostream& out, BigNumber big) {
    out << big.value();
    return out;
}

void BigNumber::filter() {
    sign = format(data);
}
void BigNumber::judge() {
    for (int i = 0; i < data.size(); i++) {
        if (isdigit(data[i])) continue;
        WARNING("invalid value: %s\n", data.c_str())
        data = "0";
        sign = 0;
        break;
    }
}
int BigNumber::format(string &s) {
    if (s == "") {
        s = "0";
        return 0;
    }
    int ind = 0, flag = (s[0] == '-');
    while (ind < s.size() - 1 && (s[ind] == '0' || s[ind] == '-' || s[ind] == '+')) ind++;
    s = string(s.begin() + ind, s.end());
    return (s == "0") ? 0 : flag;
}
int BigNumber::compare(const string &a, const string &b) {
    int lena = a.size(), lenb = b.size();
    if (lena > lenb) return 1;
    if (lena < lenb) return -1;
    for (int i = 0; i < lena; i++) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}
int BigNumber::compare(int sa, const  string &a, int sb, const string &b) {
    int code = 0, cmp = 0;
    code |= sa;
    code <<= 1;
    code |= sb;
    switch (code) {
        case 0:
            cmp = compare(a, b);
            break;
        case 1:
            cmp = 1;
            break;
        case 2:
            cmp = -1;
            break;
        case 3:
            cmp = - compare(a, b);
            break;
    }
    return cmp;
}
void BigNumber::calculate(char op, int sa, const string &a, int sb, const string &b, int &sc, string &c){
    int code = 0;
    code |= sa;
    code <<= 1;
    code |= sb;
    switch (op) {
        case '+': {
            code <<= 1;
            code |= less(a, b);
            switch (code) {
                case 0: sc = 0; c = add(a, b); break;
                case 1: sc = 0; c = add(a, b); break;
                case 2: sc = 0; c = subtract(a, b); break;
                case 3: sc = 1; c = subtract(b, a); break;
                case 4: sc = 1; c = subtract(a, b); break;
                case 5: sc = 0; c = subtract(b, a); break;
                case 6: sc = 1; c = add(a, b); break;
                case 7: sc = 1; c = add(a, b); break;
            }
        } break;
        case '-': {
            code <<= 1;
            code |= less(a, b);
            switch (code) {
                case 0: sc = 0; c = subtract(a, b); break;
                case 1: sc = 1; c = subtract(b, a); break;
                case 2: sc = 0; c = add(a, b); break;
                case 3: sc = 0; c = add(a, b); break;
                case 4: sc = 1; c = add(a, b); break;
                case 5: sc = 1; c = add(a, b); break;
                case 6: sc = 1; c = subtract(a, b); break;
                case 7: sc = 0; c = subtract(b, a); break;
            }
        } break;
        case '*': {
            switch (code) {
                case 0: sc = 0; c = multiply(a, b); break;
                case 1: sc = 1; c = multiply(a, b); break;
                case 2: sc = 1; c = multiply(a, b); break;
                case 3: sc = 0; c = multiply(a, b); break;
            }
        } break;
        case '/': {
            switch (code) {
                case 0: sc = 0; c = divide(a, b); break;
                case 1: sc = 1; c = divide(a, b); break;
                case 2: sc = 1; c = divide(a, b); break;
                case 3: sc = 0; c = divide(a, b); break;
            }
        } break;
        case '%': {
            switch (code) {
                case 0: sc = 0; c = mod(a, b); break;
                case 1: sc = 0; c = mod(a, b); break;
                case 2: sc = 1; c = mod(a, b); break;
                case 3: sc = 1; c = mod(a, b); break;
            }
        } break;
    }
    sc = (c[0] == '0') ? 0 : sc;
    return ;
}
bool BigNumber::less(const string &a, const string &b) {
    return compare(a, b) < 0;
}
bool BigNumber::less_equal(const string &a, const string &b) {
    return compare(a, b) <= 0;
}
bool BigNumber::greater(const string &a, const string &b) {
    return compare(a, b) > 0;
}
bool BigNumber::greater_equal(const string &a, const string &b) {
    return compare(a, b) >= 0;
}
bool BigNumber::equal(const string &a, const string &b) {
    return compare(a, b) == 0;
}
bool BigNumber::not_equal(const string &a, const string &b) {
    return compare(a, b) != 0;
}
string BigNumber::add(const string &a, const string &b) {
    if (a == "0") return b;
    if (b == "0") return a;
    int ia = a.size() - 1, ib = b.size() - 1;
    string ans = "";
    int flow = 0;
    while (ia >= 0 || ib >= 0) {
        char temp = '0' + flow;
        if (ia >= 0) {
            temp += a[ia] - '0';
            ia--;
        }
        if (ib >= 0) {
            temp += b[ib] - '0';
            ib--;
        }
        if (temp > '9') {
            flow = 1;
            temp -= 10;
        } else {
            flow = 0;
        }
        ans += temp;
    }
    if (flow == 1) ans += '1';
    reverse(ans.begin(), ans.end());
    format(ans);
    return ans;
}
string BigNumber::subtract(const string &a, const string &b) {
    if (b == "0") return a;
    int ia = a.size() - 1, ib = b.size() - 1;
    string ans = "";
    int borrow = 0;
    while (ia >= 0 || ib >= 0) {
        char temp = '0' - borrow;
        if (ia >= 0) {
            temp += a[ia] - '0';
            ia--;
        }
        if (ib >= 0) {
            temp -= b[ib] - '0';
            ib--;
        }
        if (temp < '0') {
            temp += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        ans += temp;
    }
    reverse(ans.begin(), ans.end());
    format(ans);
    return ans;
}
string BigNumber::multiply(const string &a, const string &b) {
    if (a == "0" || b == "0") return "0";
    int lena = a.size(), lenb = b.size();
    string *result = new string[lena + lenb];
    for (int i = 0; i < lena + lenb; i++) result[i] = "0";
    for (int i = lena - 1; i >= 0; i--) {
        for (int j = lenb - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int nowind = lena - i - 1 + lenb - j - 1;
            string muls = to_string(mul);
            result[nowind] = add(result[nowind],  muls);
        }
    }
    int index = 0;
    string ans = "";
    while (index < lena + lenb) {
        string &now = result[index];
        int len_now = now.size();
        if (len_now == 0) break;
        if (len_now > 1) {
            string flow(now.begin(), now.begin() + len_now - 1);
            result[index + 1] = add(result[index + 1], flow);
        }
        ans += now[len_now - 1];
        index++;
    }
    reverse(ans.begin(), ans.end());
    format(ans);
    delete[] result;
    return ans;
}
char BigNumber::search_digit(const string &a, const string &b) {
    char l = '0', r = '9';
    while (l < r) {
        char mid = (l + r + 1) / 2;
        string digit = "";
        digit += mid;
        string muls = multiply(b, digit);
        if (less_equal(muls, a)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}
void BigNumber::divide(const string &a, const string &b, string &ans, string &remainder) {
    ans = "";
    remainder = "";
    int lena = a.size();
    for (int i = 0; i < lena; i++) {
        remainder += a[i];
        format(remainder);
        char digit = search_digit(remainder, b);
        string ds = "";
        ds += digit;
        ans += digit;
        string muls = multiply(b, ds);
        remainder = subtract(remainder, muls);
    }
}
string BigNumber::divide(const string &a, const string &b) {
    if (b == "0") {
        WARNING("division by zero: %s / %s\n", a.c_str(), b.c_str());
        return "0";
    }
    if (a == "0") return "0";
    if (less(a, b)) return "0";
    string ans, remainder;
    divide(a, b, ans, remainder);
    format(ans);
    return ans;
}
string BigNumber::mod(const string &a, const string &b) {
    if (b == "0") {
        WARNING("division by zero: %s %% %s\n", a.c_str(), b.c_str());
        return "0";
    }
    if (a == "0") return "0";
    if (less(a, b)) return a;
    string ans, remainder;
    divide(a, b, ans, remainder);
    format(remainder);
    return remainder;
}
