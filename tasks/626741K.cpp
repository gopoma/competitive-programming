#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using str = string;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;


#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bc back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a)   FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i))
#define R0F(i,a)   ROF(i,0,a)
#define rep(a)     F0R(_,a)
#define each(a,x)  for (auto& a: x)

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}

tcT> bool ckmax(T& a, const T& b) {
    return a< b ? a = b, 1 : 0;
}

ll rng_ll(ll L, ll R) {
    return uniform_int_distribution<ll>(L,R)(rng);
}

// #define dbg(x) cerr << #x << ": " << x << endl;
#define dbg(x) 0
// #define dbg2(x, y) cerr << #x << " " << #y << " | " << x << " " << y << endl;
#define dbg2(x, y) 0

void printvec(vector<string> S) {
    for(auto& x: S) cerr << x << " ";
    cout << endl;
}

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
}

void solve() {
    int n; cin >> n;
    vector<pair<ll, ll>> a(n);
    for(auto& [x, y]: a) cin >> x >> y;

    auto area = [&](pl P1, pl P2, pl P3) -> ll {
        auto [x1, y1] = P1;
        auto [x2, y2] = P2;
        auto [x3, y3] = P3;

        ll A = x1 * y2 + x2 * y3 + x3 * y1;
        ll B = x2 * y1 + x3 * y2 + x1 * y3;
        ll S = custom_abs(A - B);
        return S;
    };


    set<pair<ll, ll>> G;
    vector<ll> dp(n);
    for(int i = 0; i < n; i++) {
        int bef = (i - 1 + n) % n;
        int nxt = (i + 1) % n;
        dp[i] = area(a[bef], a[i], a[nxt]);
        G.emplace(dp[i], i);
    }

    set<pair<ll, ll>> guarda_G = G;
    vector<ll> guarda_dp = dp;

    set<ll> order;
    for(int i = 0; i < n; i++) order.emplace(i);


    auto get_prv = [&](int id) -> ll {
        auto it = order.lower_bound(id);
        if(it == order.begin()) return *order.rbegin();
        else {
            it--;
            return *it;
        }
    };

    auto get_nxt = [&](int id) -> ll {
        auto it = order.upper_bound(id);
        if(it == order.end()) return *order.begin();
        else {
            return *it;
        }
    };

    ll sid = -1;

    auto rem = [&](int id) -> void {
        G.erase(make_pair(dp[id], id));

        int prv = get_prv(id);
        int nxt = get_nxt(id);

        order.erase(id);

        G.erase(make_pair(dp[prv], prv));
        G.erase(make_pair(dp[nxt], nxt));

        dp[prv] = area(a[get_prv(prv)], a[prv], a[get_nxt(prv)]);
        dp[nxt] = area(a[get_prv(nxt)], a[nxt], a[get_nxt(nxt)]);

        G.emplace(dp[prv], prv);
        G.emplace(dp[nxt], nxt);
    };

    auto get_mn = [&](bool adi = false) -> ll {
        auto it = *G.begin();

        auto [mn, id] = it;

        dbg("start");
        dbg(mn);
        dbg(id);

        if(adi) {
            sid = id;
        }

        rem(id);

        return mn;
    };


    bool shouldFirst = false;
    {
        ll First = 0;
        ll Second = 0;
        bool turn = true;
        for(int _ = 0; _ < n - 2; _++) {
            if(turn) {
                First += get_mn(false);
            } else {
                Second += get_mn(false);
            }
            turn = !turn;
        }
        if(First < Second) {
            shouldFirst = true;
        }

        dbg(First);
        dbg(Second);
    }

    G = guarda_G;
    dp = guarda_dp;
    for(int i = 0; i < n; i++) order.emplace(i);

    bool flag = true;
    if(shouldFirst) {
        cout << "Alberto" << endl;
        for(int _ = 0; _ < n - 2; _++) {
            if(flag) {
                get_mn(true);
                cout << sid + 1 << endl;
            } else {
                int i; cin >> i; i--;
                rem(i);
            }
            flag = !flag;
        }
    } else {
        cout << "Beatrice" << endl;
        for(int _ = 0; _ < n - 2; _++) {
            if(flag) {
                int i; cin >> i; i--;
                rem(i);
            } else {
                get_mn(true);
                cout << sid + 1 << endl;
            }
            flag = !flag;
        }

    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
