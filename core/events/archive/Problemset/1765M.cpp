#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll x = 2; x * x <= n; x++) {
        if(n % x == 0) return false;
    }
    return true;
}

ll getMinPrimeFactor(ll n) {
    // if divisible by 2
    if (n % 2 == 0)
        return 2;

    // iterate from 3 to sqrt(n)
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return i;
    }

    return n;
}

void solve() {
    ll n;
    cin >> n;

    if(n % 2 == 0) {
        cout << (n / 2) << " " << (n / 2);
    } else {
        const ll minpf = getMinPrimeFactor(n);

        if(isPrime(n)) {
            cout << 1 << " " << (n - 1);
        } else {
            const ll tmp = n / minpf;
            cout << tmp << " " << (n - tmp);
        }
    }
    cout << "\n";
}

/*
void solve() {
    ll n;
    cin >> n;
    cout << n << "\n";

    ll minLCM = LLONG_MAX;
    ll aOK, bOK;
    for(ll i = 1; i < n; i++) {
        ll a = i, b = n - i;

        ll currentLCM = (a * b) / __gcd(a, b);

        if(minLCM >= currentLCM) {
            minLCM = currentLCM;
            aOK = a;
            bOK = b;
        }
    }

    cout << aOK << " " << bOK << " minLCM: " << minLCM << "\n\n";
}
*/

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
