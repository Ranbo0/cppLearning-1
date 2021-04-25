/********************************************************************************
 *
 * @author: Cao Xingyu
 * @date: 2020-04-19
 * @description: To use pairs in unordered_map
 * @version: 1.0
 *
 ********************************************************************************/

#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

template<class T1, class T2>
struct pair_hash {
    size_t operator() (const pair<T1, T2>& p) const {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
    // <1, 2>和<2, 1>必定产生冲突的解决办法
    bool operator() (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) const {
        return equal_to<T1>()(lhs.first, rhs.first) && equal_to<T2>()(lhs.second, rhs.second);
    }
};

template <class T1, class T2>
struct pair_hash2 {
    size_t operator()(const pair<T1, T2> &p) const {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
};

int main()
{
    unordered_map<pair<int, int>, int, pair_hash<int, int>, pair_hash<int, int>> mp;
    mp.insert(make_pair(make_pair(1, 2), 3));
    mp.insert(make_pair(make_pair(2, 1), -3));

    pair<int, int> p1 = make_pair(1, 2);
    pair<int, int> p2 = make_pair(2, 1);

    cout << "mp[{1, 2}] = " << mp[p1] << ", mp[{2, 1}] = " << mp[p2] << endl;

    unordered_map<pair<int, int>, int, pair_hash2<int, int>> mp2;
    mp2.insert(make_pair(make_pair(1, 2), 3));
    mp2.insert(make_pair(make_pair(2, 1), -3));

    cout << "mp[{1, 2}] = " << mp2[p1] << ", mp[{2, 1}] = " << mp2[p2] << endl;

    unordered_map<pair<int, int>, pair<int, int>, pair_hash2<int, int>> mp3;
    unordered_map<pair<int, int>, pair<int, int>, pair_hash<int, int>> mp4;
    unordered_map<pair<int, int>, pair<int, int>, pair_hash<int, int>, pair_hash<int, int>> mp5;

    system("pause");
    return 0;
}
