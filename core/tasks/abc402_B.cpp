#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

#define dbg(x) cout << "Line(" << __LINE__ << "): " << #x << ": " << x << endl;
#define GA     debug(0)
#define RAYA   cout << "================================" << endl;

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> q;
    deque<int> d;
    for(int _ = 0; _ < q; _++) {
        int ty; cin >> ty;
        if(ty == 1) {
            int X; cin >> X;
            d.emplace_back(X);
        } else {
            cout << d.front() << "\n";
            d.pop_front();
        }
    }
}
