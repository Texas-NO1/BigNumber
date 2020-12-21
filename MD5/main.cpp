/*************************************************************************
	> File Name: main.cpp
	> Author: aqx
	> Mail: qx.ai@qq.com
	> Created Time: Mon 21 Dec 2020 06:07:27 PM CST
 ************************************************************************/
#include <iostream>
#include "md5.h"

using std::cin;
using std::cout;
using std::endl;

void printMD5(const string& message) {
  cout << "结果：md5(\"" << message << "\") = "
       << MD5(message).toStr() << endl;
}

int main() {
    cout << "测试用例：" << endl;
    printMD5("");
    printMD5("a");
    printMD5("abc");
    printMD5("message digest");
    printMD5("abcdefghijklmnopqrstuvwxyz");
    printMD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    cout << "输入加密信息：" << endl;
    string str;
    while (true) {
        cin >> str;
        printMD5(str);
    }
	return 0;
}
