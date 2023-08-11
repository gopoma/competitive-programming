#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    string leftStr  = "qwertasdfgzxcvb", rightStr = "yuiophjklnm";
    unordered_set<char> left, right;

    for(auto c: leftStr) left.insert(c);
    for(auto c: rightStr) right.insert(c);

    string s;
    cin >> s;

    bool isLeft = left.count(s[0]) == 1;
    isLeft = !isLeft;

    for(ll i = 1; i < s.size(); i++) {
        if(isLeft) {
            if(left.count(s[i]) == 0) {
                cout << "no\n";
                return;
            }
        } else {
            if(right.count(s[i]) == 0) {
                cout << "no\n";
                return;
            }
        }

        isLeft = !isLeft;
    }

    cout << "yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
