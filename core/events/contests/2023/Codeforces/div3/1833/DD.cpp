#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n; cin >> n;

    ll p[n], pSorted[n];
    for(ll i = 0; i < n; i++) {
        cin >> p[i];
        pSorted[i] = p[i];
    }

    sort(pSorted, pSorted + n);

    if(n == 1) {
        cout << p[0] << "\n";
        return;
    }

    ll pMax = pSorted[n - 1];
    ll pMaxIndex;
    ll pSecondLargest = pMax - 1;
    ll pSecondLargestIndex;

    for(ll i = 0; i < n; i++) {
        if(p[i] == pMax) {
            pMaxIndex = i;
            break;
        }
    }

    for(ll i = 0; i < n; i++) {
        if(p[i] == pSecondLargest) {
            pSecondLargestIndex =  i;
            break;
        }
    }



    ll result[n];
    ll cc = 0;
    for(ll i = 1; i < n; i++) {
        result[cc++] = p[i];
    }
    result[cc] = p[0];

    ll r = (p[0] == pMax) ? pSecondLargestIndex - 1 : pMaxIndex - 1;
    if(p[n - 1] == pMax || (p[0] == pMax && p[n - 1] == pSecondLargest)) {
        r++;
    }
    for(ll l = r; l >= 0; l--) {
        ll partial[n];
        ll counter = 0;

        for(ll i = r + 1; i < n; i++)
            partial[counter++] = p[i];

        for(ll i = r; i >= l; i--)
            partial[counter++] = p[i];

        for(ll i = 0; i < l; i++)
            partial[counter++] = p[i];

        bool found = false;

        for(ll i = 0; i < n; i++) {
            if(result[i] > partial[i])
                break;

            if(result[i] < partial[i]) {
                found = true;
                break;
            }
        }

        if(found) {
            for(ll i = 0; i < n; i++) {
                result[i] = partial[i];
            }
        }
    }



    for(ll i = 0; i < n - 1; i++) {
        cout << result[i] << " ";
    }
    cout << result[n - 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
