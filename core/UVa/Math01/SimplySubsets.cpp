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
    auto get = [&](string& S) -> set<ll> {
        set<ll> ans;
        string current;
        for(auto& c: S) {
            if(c == ' ') {
                if(!current.empty())
                    ans.emplace(stoll(current));
                current.clear();
            } else {
                current.push_back(c);
            }
        }
        if(!current.empty())
            ans.emplace(stoll(current));
        return ans;
    };
    auto in = [&](set<ll>& A, set<ll>& B) -> bool {
        bool ok = true;
        for(auto& x: A) ok &= B.count(x);
        return ok;
    };
    string A_str, B_str;
    while(getline(cin, A_str) && getline(cin, B_str)) {
        set<ll> A = get(A_str);
        set<ll> B = get(B_str);
        dbg(A_str, B_str);
        dbg(A, B);
        if(A == B) cout << "A equals B\n";
        else if(in(A, B)) cout << "A is a proper subset of B\n";
        else if(in(B, A)) cout << "B is a proper subset of A\n";
        else {
            set<ll> Xd;
            for(auto& x: A) Xd.emplace(x);
            for(auto& x: B) Xd.emplace(x);
            if(int(Xd.size()) == (int(A.size()) + int(B.size()))) cout << "A and B are disjoint\n";
            else cout << "I'm confused!\n";
        }
        RAYA;
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
