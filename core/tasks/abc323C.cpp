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

void solve() {
    int N, M;
    cin >> N >> M;

    vector<int> problem_scores(M);
    for(auto& e: problem_scores) {
        cin >> e;
    }

    vector<string> partial_results(N);
    for(auto& e: partial_results) {
        cin >> e;
    }

    vector<int> partial_scores(N);
    for(int i = 0; i < N; i++) {
        partial_scores[i] = i + 1;
        for(int j = 0; j < M; j++) {
            if(partial_results[i][j] == 'o') {
                partial_scores[i] += problem_scores[j];
            }
        }
    }

    // DBG(problem_scores);
    // DBG(partial_scores);

    int max_score = *max_element(all(partial_scores));
    // DBG(max_score);

    map<int, int> aux;
    for(auto& e: partial_scores) {
        aux[e]++;
    }

    for(int i = 0; i < N; i++) {
        if(partial_scores[i] == max_score) {
            if(aux[max_score] == 1) {
                cout << "0\n";
            } else {
                cout << "1\n";
            }
        } else {
            vector<int> allowables;
            for(int j = 0; j < M; j++) {
                if(partial_results[i][j] == 'x') {
                    allowables.eb(problem_scores[j]);
                }
            }
            sort(allowables.rbegin(), allowables.rend());

            int current_score = partial_scores[i];
            int ans = 0;
            while(current_score < max_score) {
                current_score += allowables[ans++];
            }
            cout << ans << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
