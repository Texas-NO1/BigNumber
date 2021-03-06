/*************************************************************************
	> File Name: bignumber.h
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Fri 18 Dec 2020 12:31:27 PM CST
 ************************************************************************/

#ifndef _BIGNUMBER_H
#define _BIGNUMBER_H
class BigNumber {
//对外开放接口，重载操作符
public:
    BigNumber();
    BigNumber(const std::string &);
    BigNumber(const long long);
    BigNumber(const BigNumber &);
    bool operator<(const BigNumber &);
    bool operator<=(const BigNumber &);
    bool operator==(const BigNumber &);
    bool operator>(const BigNumber &);
    bool operator>=(const BigNumber &);
    bool operator!=(const BigNumber &);
    BigNumber operator+(const BigNumber &);
    BigNumber operator-(const BigNumber &);
    BigNumber operator*(const BigNumber &);
    BigNumber operator/(const BigNumber &);
    BigNumber operator%(const BigNumber &);
    BigNumber& operator+=(const BigNumber &);
    BigNumber& operator-=(const BigNumber &);
    BigNumber& operator*=(const BigNumber &);
    BigNumber& operator/=(const BigNumber &);
    BigNumber& operator%=(const BigNumber &);
    int compare(const BigNumber&);
    std::string value() const;
    int length() const;
    bool isodd() const;
    friend std::istream& operator>>(std::istream&, BigNumber&);//输入传引用，因为必须对具体的BigNumber对象进行输入
    friend std::ostream& operator<<(std::ostream&, BigNumber);//输出传对象，因为既可以输出对象也可以输出临时产生的变量，如运算的返回值
private:
    int sign;
    std::string data;
    //底层函数
    BigNumber(const int, const std::string &);//用符号和数值进行赋值，不公开
    void filter();//将data过滤成,一个非负数和一个符号位，规定0符号为+
    void judge();//由string初始化后的data是否为有效数字
    int format(std::string &);//格式化字符串，消除前置0和符号位，并返回符号位
    int compare(const std::string &, const std::string &);//非负数比较函数的底层函数
    int compare(int, const std::string &, int, const std::string &);//带符号比较函数
    void calculate(char, int, const std::string &, int, const std::string &, int &, std::string &);// 符号数计算器，计算得到的结果c_sign和c_data以参数形式返回
    char search_digit(const std::string &, const std::string &);//二分查找最后一个满足a=b*digit的digit, 除余算法用
    void divide(const std::string &, const std::string &, std::string &, std::string &);//除余算法的底层函数
    //标准非负数比较
    bool less(const std::string &, const std::string &);//a<b
    bool less_equal(const std::string &, const std::string &);//a<=b
    bool greater(const std::string &, const std::string &);//a>b
    bool greater_equal(const std::string &, const std::string &);//a>=b
    bool equal(const std::string &, const std::string &);//a==b
    bool not_equal(const std::string &, const std::string &);//a!=b
    //标准非负数计算, 返回值也为非负数
    std::string add(const std::string &, const std::string &);//非负数a+b
    std::string subtract(const std::string &, const std::string &);//非负数a-b,且a>=b
    std::string multiply(const std::string &, const std::string &);//非负数a*b
    std::string divide(const std::string &, const std::string &);//非负数a/b
    std::string mod(const std::string &, const std::string &);//非负数a%b
};
#endif
