#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    const ll limit = LONG_MAX;

    ll min01 = limit;
    ll min10 = limit;
    ll min11 = limit;

    for(int i = 0; i < n; i++) {
        ll m;
        cin >> m;

        string s;
        cin >> s;

        if(s == "01") {
            min01 = min(min01, m);
        } else if(s == "10") {
            min10 = min(min10, m);
        } else if(s == "11") {
            min11 = min(min11, m);
        }
    }

    if((min01 == limit || min10 == limit) && min11 == limit) {
        cout << -1 << endl;
    } else {
        cout << min(min01 + min10, min11) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
