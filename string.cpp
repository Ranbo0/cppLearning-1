/********************************************************************************
 *
 * @author: Cao Xingyu
 * @date: 2021-04-26
 * @description: 
 * @version: 1.0
 * @conditions: 
 *
 ********************************************************************************/

#include <bits/stdc++.h>

using namespace std;

int main() {
    /****string to const char* ****/
    string s1 = "string s1";
    const char *cstr1 = s1.c_str();
    cout << "s1(string) = " << s1 << ", s1 convert to cstr1 is : cstr1(const char*) = " << cstr1 << endl;

    /****const char* to string****/
    const char *cstr2 = "const char* cstr2";
    string s2(cstr2);
    cout << "cstr2(const char *) = " << cstr2 << ", cstr2 convert to s2 is : s2(string) = " << s2 << endl;

    /****string to char* ****/
    string s3 = "string s3";
    char *str1;
    int len_s3 = s3.size();
    str1 = new char[len_s3 + 1];
    strcpy(str1, s3.c_str());
    cout << "s3(string) = " << s3 << ", s3 convert to str1 is : str1(char*) = " << str1 << endl;

    /****char* to string****/
    char *str2 = "char* str2";
    string s4(str2);
    cout << "str2(char *) = " << str2 << ", str2 convert to s4 is : s4(string) = " << s4 << endl;

    /****const char* to char* ****/
    const char *cstr3 = "const char* cstr3";
    int n = strlen(cstr3);
    char *str3;
    str3 = new char[n];
    strcpy(str3, cstr3);
    cout << "cstr3(const char *) = " << cstr3 << ", cstr3 convert to str3 is : str3(char*) = " << str3 << endl;

    /****char* to const char* ****/
    char *str4 = "char* str4";
    const char *cstr4 = str4;
    cout << "str4(char *) = " << str4 << ", str4 convert to cstr4 is : cstr4(const char*) = " << cstr4 << endl;

    system("pause");
    return 0;
}
