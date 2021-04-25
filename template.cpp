/********************************************************************************
 *
 * @author: Cao Xingyu
 * @date: 
 * @description: 
 * @version: 1.0
 * @conditions: 
 *
 ********************************************************************************/

#include <bits/stdc++.h>

using namespace std;

template<class T>
class Stack {
private:
    vector<T> bot;
    int maxSize;

public:
    void push(T const &);
    void pop();
    T top() const;
    bool empty() const;
    unsigned int size() const;
};

template<class T>
void Stack<T>::push(T const &elem) {
    bot.emplace_back(elem);
}

template<class T>
void Stack<T>::pop() {
    if (bot.empty()) {
        throw out_of_range("Stack<>::pop() : Empty stack.");
    }
    bot.pop_back();
}

template<class T>
T Stack<T>::top() const {
    if (bot.empty()) {
        throw out_of_range("Stack<>::top() : Empty stack.");
    }
    return bot.back();
}

template<class T>
bool Stack<T>::empty() const {
    return bot.empty();
}

template<class T>
unsigned int Stack<T>::size() const {
    return bot.size();
}

int main()
{
    srand(time(0));
    try {
        Stack<int> s1;
        Stack<string> s2;

        int i = 1;
        while (i & 1) {
            i = rand() % 100;
            s1.push(i);
        }

        cout << "s1.size() = " << s1.size() << endl;

        i = 1;
        while (i & 1) {
            i = rand() % 100;
            if (i < 50) {
                s2.push("Hello");
            } else {
                s2.push("world");
            }
        }

        cout << "s2.size() = " << s2.size() << endl;

        for (int i = 0; i < 5; ++i) {
            s1.pop();
            s2.pop();
        }
    }
    catch (exception const& exc) {
        cerr << "Exception : " << exc.what() << endl;

        return -1;
    }

    system("pause");
    return 0;
}
