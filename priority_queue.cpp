/********************************************************************************
 *
 * @author: Cao Xingyu
 * @date: 2020-04-19
 * @description: An self-defined method to sort the element in the priority_queue
 * @version: 1.0
 * @conditions: Use when need to customize the sorting method
 *
 ********************************************************************************/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int i = 0;
    srand((int)time(0));
    priority_queue<int> q0; //default, front is the largest, top heap
    for (i = 0; i < 10; ++i) {
        int num = rand() % 100;
        q0.push(num);
    }
    cout << "************************************************\n";

    i = 0;
    while (!q0.empty()) {
        cout << ++i << ": q0.top() = " << q0.top() << endl;
        q0.pop();
    }

    cout << "************************************************\n\n";

    priority_queue<int, vector<int>, greater<int>> q1;  // use greater<int>() to get a min heap, front is the smallest
    for (i = 0; i < 10; ++i) {
        int num = rand() % 100;
        q1.push(num);
    }

    cout << "************************************************\n";

    i = 0;
    while (!q1.empty()) {
        cout << ++i << ": q1.top() = " << q1.top() << endl;
        q1.pop();
    }
    cout << "************************************************\n\n";

    priority_queue<int, vector<int>, less<int>> q2;     //equal to q0(default), front is the largest

    for (i = 0; i < 10; ++i) {
        int num = rand() % 100;
        q2.push(num);
    }

    cout << "************************************************\n";

    i = 0;
    while (!q2.empty()) {
        cout << ++i << ": q2.top() = " << q2.top() << endl;
        q2.pop();
    }
    cout << "************************************************\n\n";

/********************************************************************************
 * 
 * some examples:
 *
 * cmp0 : equals to default settings, a top heap, the front element is the largest one
 * 
 * cmp1 : a min heap, the front element is the smallest one
 * 
 * cmp2 : sorted into odd numbers and even ones, even number takes precedence over odd ones, even decending, odd ascending
 * 
 * cmp3 : sorted into odd numbers and even ones, odd number takes precedence over even ones, even decending, odd ascending
 * 
 * cmp4 : use when the elements are pairs, decending by the first element, ascending by the second element while the first elements are equal
 *
 ********************************************************************************/

    auto cmp0 = [&](const auto &u, const auto &v) {     // top heap, equals to q0(default), front is the largest
        return u < v;
    };

    auto cmp1 = [&](const auto &u, const auto &v) {     // min heap, equals to q1, front is the smallest
        return u > v;
    };

    priority_queue<int, vector<int>, decltype(cmp0)> self_q0(cmp0);
    for (i = 0; i < 10; ++i) {
        int num = rand() % 100;
        self_q0.push(num);
    }

    cout << "************************************************\n";

    i = 0;
    while (!self_q0.empty()) {
        cout << ++i << ": self_q0.top() = " << self_q0.top() << endl;
        self_q0.pop();
    }
    cout << "************************************************\n\n";

    priority_queue<int, vector<int>, decltype(cmp1)> self_q1(cmp1);
    for (i = 9; i >= 0; --i) {
        int num = rand() % 100;
        self_q1.push(num);
    }

    cout << "************************************************\n";

    while (!self_q1.empty())
    {
        cout << ++i << ": self_q1.top() = " << self_q1.top() << endl;
        self_q1.pop();
    }
    cout << "************************************************\n\n";

    auto cmp2 = [&](const auto &u, const auto &v) {     //even number takes precedence over odd ones, while even descending and odd ascending
        if (u & 1) {
            if (v & 1) {        // u is odd, v is odd, odd numbers are sorted in an ascending order
                return u > v;
            }
            return true;        // u is odd, v is even, v takes precedence over u
        } else {
            if (v & 1) {
                return false;   // v is odd, u is even, u takes precedence over v
            } else {
                return u < v;   // u is even, v is even, even numbers are sorted in a decending order
            }
        }
    };

    priority_queue<int, vector<int>, decltype(cmp2)> self_q2(cmp2);
    for (i = 9; i >= 0; --i) {
        int num = rand() % 100;
        self_q2.push(num);
    }

    cout << "************************************************\n";

    while (!self_q2.empty()) {
        cout << ++i << ": self_q2.top() = " << self_q2.top() << endl;
        self_q2.pop();
    }
    cout << "************************************************\n\n";

    auto cmp3 = [&](const auto &u, const auto &v) { // odd number takes precedence over even ones, while odd ascending and even decending
        if (u & 1) {
            if (v & 1) {
                return u > v;       // u is odd, v is odd, odd numbers are sorted in an ascending order
            }
            return false;           // u is odd, v is even, u takes precedence over v
        } else {
            if (v & 1) {
                return true;        // u is even, v is odd, v takes precedence over u
            } else {
                return u < v;       // u is even, v is even, even numbers are sorted in a decending order
            }
        }
    };

    priority_queue<int, vector<int>, decltype(cmp3)> self_q3(cmp3);
    for (i = 9; i >= 0; --i) {
        int num = rand() % 100;
        self_q3.push(num);
    }

    cout << "************************************************\n";

    while (!self_q3.empty()) {
        cout << ++i << ": self_q3.top() = " << self_q3.top() << endl;
        self_q3.pop();
    }
    cout << "************************************************\n\n";

    auto cmp4 = [&](const auto &u, const auto &v) { // decending by the first element, ascending by the second element while the first elements are equal
        if (u.first != v.first) {
            return u.first < v.first;
        }
        return u.second > v.second;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp4)> self_q4(cmp4);

    for (i = 9; i >= 0; --i) {
        int num1 = rand() % 100;
        int num2 = rand() % 100;
        self_q4.push(make_pair(num1, num2));
    }

    cout << "************************************************\n";

    while (!self_q4.empty())
    {
        cout << ++i << ": self_q4.top() = {" << self_q4.top().first << ", " << self_q4.top().second << "}" << endl;
        self_q4.pop();
    }
    cout << "************************************************\n\n";



    system("pause");
    return 0;
}
