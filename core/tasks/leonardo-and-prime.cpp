#include <bits/stdc++.h>

using namespace std;

bool isPrime(long long x) {
    for(long long i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;

    return (x >= 2);
}

vector<long long> precompute() {
    vector<long long> primes;
    for(long long x = 1; x <= 47; x++)
        if(isPrime(x)) primes.emplace_back(x);

    return primes;
}

int primeCount(long long n) {
    vector<long long> primes = precompute();
    // for(auto& p: primes) cout << "p: " << p << "\n";

    int ans = -1;
    long long acc = 1;
    for(int i = 0; i < int(primes.size()); i++) {
        acc *= primes[i];
        if(acc > n) {
            ans = i;
            break;
        }
    }
    if(ans == -1) ans = 15;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;

    for(int _ = 0; _ < q; _++) {
        long long n;
        cin >> n;

        cout << primeCount(n) << "\n";
    }

}
