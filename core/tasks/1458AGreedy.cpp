#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << "\n"
#define all(x) x.begin(), x.end()

using ll = long long;
using vl = vector<ll>;

signed main() {
    // <>
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;

    vl a(n); for(auto& x: a) cin >> x;
    vl b(m); for(auto& x: b) cin >> x;

    dbg(n);
    dbg(m);

    assert(a.size() == n);
    assert(b.size() == m);

    {
        bool ok = true;
        ll tar = a.front();
        for(auto& x: a) ok &= (x == tar);

        if(ok) {
            dbg("here");
            vl ans;
            for(int i = 0; i < m; i++) {
                ans.emplace_back(tar + b[i]);
            }
            for(auto& x: ans) cout << x << " ";
            cout << "\n";

            exit(0);
        }
    }

    vl norm(n);
    ll mn = *min_element(all(a));

    dbg(mn);

    ll g = 0;
    for(int i = 0; i < n; i++) {
        norm[i] = a[i] - mn;

        g = gcd(g, norm[i]);
    }

    dbg(g);

    vl ans;
    for(int i = 0; i < m; i++) {
        ll tar = b[i] + mn;

        if(g % tar == 0 || tar % g == 0) {
            ans.emplace_back(min(g, tar));
        } else {
            ans.emplace_back(1);
        }
    }

    for(auto& x: ans) cout << x << " ";
    cout << "\n";
}
