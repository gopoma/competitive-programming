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

// Direction vectors
ll dRow[] = { -1LL, 0LL, 1LL,  0LL };
ll dCol[] = {  0LL, 1LL, 0LL, -1LL };

void solve() {
    int R, C;
    cin >> R >> C;

    int mtx[R][C];
    set<int> temp;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> mtx[i][j];
            temp.ins(mtx[i][j]);
        }
    }
    assert(sz(temp) == R * C);

    ll global_ans = -1LL;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {

            bool visited[R][C];
            for(int k = 0; k < R; k++) {
                for(int l = 0; l < C; l++) {
                    visited[k][l] = false;
                }
            }

            // queue<pair<ll, ll>> q;
            priority_queue<pair<ll, pair<ll, ll>>, vector<pair<ll, pair<ll, ll>>>, greater<pair<ll, pair<ll, ll>>>> pq;

            visited[i][j] = true;
            pq.push(make_pair(mtx[i][j], make_pair(i, j)));

            ll partial = 0LL;

            while(!pq.empty()) {
                auto cell = pq.top();
                pq.pop();

                ll x = cell.second.first;
                ll y = cell.second.second;

                partial++;

                for(ll k = 0; k < 4; k++) {
                    ll adjx = x + dRow[k];
                    ll adjy = y + dCol[k];

                    if(!(adjx < 0 || adjy < 0 || adjx >= R || adjy >= C || visited[adjx][adjy] || mtx[adjx][adjy] < mtx[x][y])) {
                        pq.push(make_pair(mtx[adjx][adjy], make_pair(adjx, adjy)));
                        visited[adjx][adjy] = true;
                    }
                }
            }

            global_ans = max(global_ans, partial);
        }
    }
    assert(global_ans != -1LL);
    cout << global_ans << n_l;
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
