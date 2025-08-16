#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

ll query(vector<ll>& pref, int L, int R) {
    const ll n = int(pref.size());

    if(L < 0 || R < 0 || L > R || L >= n || R >= n) return 0;

    ll sum = pref[R];
    if(0 <= L - 1) sum -= pref[L - 1];

    return sum;
}

ll n;
string S;
vector<ll> ones;

const ll BIG = ll(1e18) + 5;

bool vis[ll(2e5) + 5];
ll  memo[ll(2e5) + 5];

ll dp(int i) {
    if(i == n) return 0;

    if(vis[i]) return memo[i];
    vis[i] = true;

    ll re = BIG;

    // start here
    re = min(re, query(ones, i + 1, n - 1) + ll(S[i] == '0'));

    // try to continue
    re = min(re, dp(i + 1) + ll(S[i] == '0'));

    return memo[i] = re;
}

void solve() {
    cin >> n;
    cin >> S;

    for(int i = 0; i <= n; i++) vis[i] = false;

    ones.resize(n);
    vector<ll> zeros(n);
    for(int i = 0; i < n; i++) {
        ones[i] = ll(S[i] == '1');
        zeros[i] = ll(S[i] == '0');
    }
    for(int i = 1; i < n; i++) {
        ones[i] += ones[i - 1];
        zeros[i] += zeros[i - 1];
    }

    ll re = BIG;
    {
        ll cnt = 0;
        for(int i = 0; i < n; i++)
            cnt += (S[i] == '1');
        re = min(re, cnt);
    }

    for(int i = 0; i < n; i++) {
        ll cur = query(ones, 0, i - 1);
        cur += dp(i);
        re = min(re, cur);
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
