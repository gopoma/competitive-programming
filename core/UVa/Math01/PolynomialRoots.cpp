#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "helpers/debug.h"

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define RAYA
#endif

template<class T> using V = vector<T>;
#define all(x) begin(x), end(x)

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

using ll = long long;
using db = long double;

void solve() {
    ll n; cin >> n;
    vector<db> A(n + 1); for(auto& x: A) cin >> x;
    vector<db> roots(n - 2); for(auto& x: roots) cin >> x;
    dbg(n);
    dbg(A);
    dbg(roots);
    auto Ruffini = [&](vector<db>& P, db x) -> vector<db> {
        assert(!P.empty());
        const int N = int(P.size());
        vector<db> ans;
        ans.emplace_back(P.front());
        db current = ans.back();
        for(int i = 1; i < N; i++) {
            db xd = current * x;
            ans.emplace_back(xd + P[i]);
            current = ans.back();
        }
        assert(!ans.empty());
        ans.pop_back();
        return ans;
    };
    vector<db> B = A;
    for(auto& x: roots) B = Ruffini(B, x);
    assert(int(B.size()) == 3);
    dbg(B);
    {
        db a = B[0];
        db b = B[1];
        db c = B[2];

        db delta = sqrtl(b * b - db(4) * a * c);
        db x = (-b + delta) / (db(2) * a);
        db x2 = (-b - delta) / (db(2) * a);
        dbg(x, x2);
        if(x < x2) swap(x, x2);
        cout << x << "\n";
        cout << x2 << "\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cout << fixed << setprecision(1);
    cerr << fixed << setprecision(1);

    int t = 1;
    cin >> t;

    for(int idx = 0; idx < t; idx++) {
        RAYA;
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
