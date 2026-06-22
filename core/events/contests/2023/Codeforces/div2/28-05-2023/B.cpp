#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

void solve() {
    ll n; cin >> n;
    ll a[n], b[n];

    for(ll& aa: a)
        cin >> aa;

    for(ll& bb: b)
        cin >> bb;

    map<ll, ll> A;
    ll num = a[0], counter = 1;
    for(ll i = 1; i < n; i++) {
        if(a[i] != num) {
            A[num] = max(A[num], counter);
            num = a[i];
            counter = 1;
        } else {
            counter++;
        }
    }
    A[num] = max(A[num], counter);

    map<ll, ll> B;
    num = b[0], counter = 1;
    for(ll i = 1; i < n; i++) {
        if(b[i] != num) {
            B[num] = max(B[num], counter);
            num = b[i];
            counter = 1;
        } else {
            counter++;
        }
    }
    B[num] = max(B[num], counter);

    ll result = -1;
    for(auto aa: A) {
        if(B[aa.first] == 0) {
            result = max(result, aa.second);
        } else {
            result = max(result, aa.second + B[aa.first]);
        }
    }

    for(auto bb: B) {
        if(A[bb.first] == 0) {
            result = max(result, bb.second);
        }
    }

    cout << result << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
