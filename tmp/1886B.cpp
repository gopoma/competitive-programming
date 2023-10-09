#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

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

const double EPS = 0.0000000001;

double distance(pair<double, double> A, pair<double, double> B) {
    return sqrt((A.first - B.first) * (A.first - B.first)
                + (A.second - B.second) * (A.second - B.second));
}

bool eq(double A, double B) {
    return A - B < EPS;
}

bool inside(pair<double, double> C, double rad, pair<double, double> P) {
    return distance(C, P) < rad || eq(distance(C, P), rad);
}

bool unite(pair<double, double> C1, double r1, pair<double, double> C2, double r2) {
    return distance(C1, C2) <= (r1 + r2) || eq(distance(C1, C2), r1 + r2);
}

void solve() {
    pair<double, double> origin = make_pair(0.0, 0.0);
    pair<double, double> P;
    pair<double, double> A;
    pair<double, double> B;
    cin >> P.first >> P.second >> A.first >> A.second >> B.first >> B.second;

    auto check = [&](double w) {
        bool ok1 = inside(A, w, origin) && inside(A, w, P);
        bool ok2 = inside(B, w, origin) && inside(B, w, P);
        bool ok3 = (
            ((inside(A, w, origin) && inside(B, w, P)) || (inside(B, w, origin) && inside(A, w, P)))
             && unite(A, w, B, w));

        return ok1 || ok2 || ok3;
    };

    double l_real = 0.0, r_real = double(1e16);
    long long l = reinterpret_cast<long long&>(l_real);
    long long r = reinterpret_cast<long long&>(r_real);
    while (l < r) {
        long long mid = l + (r - l) / 2;
        if (check(reinterpret_cast<double&>(mid)))
            r = mid;
        else
            l = mid + 1;
    }

    double ans = reinterpret_cast<double&>(l);
    cout << ans << n_l;
}

int main() {
    cout << fixed << setprecision(12);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
