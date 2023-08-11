#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

ll lcm(ll a, ll b) {
    return (a * b) / __gcd(a, b);
}

void solve() {
    ll k, l, m, n, d; cin >> k >> l >> m >> n >> d;

    // k l m n
    ll N1 = d/k + d/l + d/m + d/n;

    // kl km kn lm ln mn
    ll N2 = d/lcm(k, l) + d/lcm(k, m) + d/lcm(k, n) + d/lcm(l, m) + d/lcm(l, n) + d/lcm(m, n);

    // klm kln lmn
    ll N3 = d/lcm(lcm(k, l), m) + d/lcm(lcm(k, l), n) + d/lcm(lcm(k, m), n) + d/lcm(lcm(l, m), n);

    ll N4 = d/lcm(lcm(k, l), lcm(m, n));

    cout << (N1 - N2 + N3 - N4) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;

    while(t--)
        solve();

    return 0;
}
