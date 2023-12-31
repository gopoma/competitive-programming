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

void brute(int N) {
    long long G = 0LL;

    for(int i = 1; i < N; i++) {
        for(int j = i + 1; j <= N; j++) {
            G += (long long)(__gcd(i, j));
        }
    }

    cout << G << n_l;
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

long long FF[MAXN];
// FF[N] = gcd(1, N) + gcd(2, N) + gcd(3, N) + ... + gcd(4, N)
// FF[N] = (for each d in divisors) partial += d * phi[N / d] -> partial
long long dp[MAXN];
void precompute() {
    precompute_phi();

    for(int i = 1; i < MAXN; i++) {
        for(int j = i; j < MAXN; j += i) {
            FF[j] += i * phi[j/i];
        }
    }

    for(int i = 0; i < MAXN; i++)
        dp[i] = 0LL;

    for(int i = 1; i < MAXN; i++)
        dp[i] = dp[i - 1] + FF[i] - i;
}

void solve2(int N) {
    assert(1 < N && N < 1000010);
    long long ans = dp[N];
    cout << ans << n_l;
}

int N;
void solve() {
    while(true) {
        cin >> N;

        if(N == 0) return;

        // brute(N);
        solve2(N);
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
