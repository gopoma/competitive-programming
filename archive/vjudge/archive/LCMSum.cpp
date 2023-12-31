#pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

#define mp  make_pair
#define F   first
#define S   second

#define sz(x)   int((x).size())
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

#define lb lower_bound
#define ub upper_bound

const int MOD = (int)1e9 + 7;   // 998244353;
const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

struct primeFactorization {
    // to store the prime factor
    // and its highest power
    int countOfPf, primeFactor;
};

vector<int> divisors;

// Recursive function to generate all the
// divisors from the prime factors
void generateDivisors(int curIndex, int curDivisor,
                      vector<primeFactorization>& arr) {
    // Base case i.e. we do not have more
    // primeFactors to include
    if (curIndex == int(arr.size())) {
        divisors.eb(curDivisor);
        return;
    }

    for (int i = 0; i <= arr[curIndex].countOfPf; ++i) {
        generateDivisors(curIndex + 1, curDivisor, arr);
        curDivisor *= arr[curIndex].primeFactor;
    }
}

// Function to find the divisors of n
vector<primeFactorization> findDivisors(int n) {
    // To store the prime factors along
    // with their highest power
    vector<primeFactorization> arr;

    // Finding prime factorization of n
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count += 1;
            }

            // For every prime factor we are storing
            // count of it's occurrenceand itself.
            arr.push_back({ count, i });
        }
    }

    // If n is prime
    if (n > 1) {
        arr.push_back({ 1, n });
    }

    return arr;
}

const int MAXN = 1000042;
vector<int> phi(MAXN + 1);
void precompute_phi() {
    for (int i = 0; i <= MAXN; i++)
        phi[i] = i;

    for (int i = 2; i <= MAXN; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= MAXN; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

void precompute() {
    precompute_phi();
}

int __lcm(int a, int b) {
    return (a*b) / __gcd(a, b);
}

int brute(int x) {
    int ans = 0;

    for(int i = 1; i <= x; i++)
        ans += __lcm(i, x);

    return ans;
}

void bulk_brute() {
    int n = 100;

    for(int x = 1; x <= n; x++)
       cout << brute(x) << n_l;
}

void solve2() {
    int n;
    cin >> n;

    vector<primeFactorization> factorization = findDivisors(n);

    int curIndex = 0, curDivisor = 1;

    // Generate all the divisors
    generateDivisors(curIndex, curDivisor, factorization);

    long long partial = 0LL;
    for(auto& d: divisors) {
        // DBG2(d, phi[d]);
        partial += (long long)(d) * (long long)(phi[d]);
    }

    long long ans = (long long)(n) * (1LL + partial) / 2LL;
    cout << ans << n_l;

    divisors.clear();
}

void solve() {
    // bulk_brute();
    solve2();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
