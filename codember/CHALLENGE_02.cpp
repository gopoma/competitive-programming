#include <bits/stdc++.h>

using namespace std;

signed main() {
    freopen("CHALLENGE_02.in", "r", stdin);
    freopen("CHALLENGE_02.out", "w", stdout);

    string input;
    cin >> input;

    long long x = 0;
    for(char& c: input) {
        if(c == '#') x++;
        else if(c == '@') x--;
        else if(c == '*') x *= x;
        else if(c == '&') cout << x;
        else assert(false);
    }
}
