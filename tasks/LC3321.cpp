#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
 
using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define ts to_string

#define lb lower_bound
#define ub upper_bound



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



//? Template
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//? /Template

vector<long long> brute(vector<int>& nums, int k, int x) {
    const int n = sz(nums);
    deque<ll> arr;
    for(int i = 0; i < k; i++) arr.eb(nums[i]);
    
    vl ans;
    auto calc = [&]() {
        map<ll, ll> hist;
        each(x, arr) hist[x]++;
        vpl order;
        for(auto& [val, cnt]: hist) order.eb(cnt, val);
        sort(rall(order));
        const int N = sz(order);
        ll sum = 0;
        for(int i = 0; i < min(N, x); i++) sum += order[i].f * order[i].s;
        ans.eb(sum);
    };

    calc();
    for(int i = k; i < n; i++) {
        arr.pop_front();
        arr.eb(nums[i]);
        calc();
    }
    return ans;
}

vector<long long> slv(vector<int>& nums, int k, int x) {
    //? <>
    set<pl> order; //? ..., mx
    map<ll, ll> hist;
    
    const pl NOTHING = mp(-1, -1);
    pl last = NOTHING;
    ll countRight = -79;

    ll sum = 0;

    auto norm = [&]() {
        if(last == NOTHING) return;
        auto itCurrentLast = order.find(last);
        //? dbg("norm! 1", *itCurrentLast, countRight, sum, order);
        while(countRight < x) { //? to left
            if(itCurrentLast == order.begin()) break;
            else {
                itCurrentLast--;
                sum += (*itCurrentLast).f * (*itCurrentLast).s;
                countRight++;
            }
        }
        //? dbg("norm! 2", *itCurrentLast, countRight, sum);
        
        while(countRight > x) { //? to right
            sum -= (*itCurrentLast).f * (*itCurrentLast).s;
            itCurrentLast++;
            countRight--;
        }

        //? dbg("norm! 3", *itCurrentLast, countRight, sum);
        
        last = *itCurrentLast;
    };

    auto delRegistry = [&](ll val, ll cnt) {
        {
            auto it = order.find(mp(cnt, val));
            chk(it != order.end());
            chk(last != NOTHING);
        }
        if(last <= mp(cnt, val)) sum -= val * cnt;

        auto itCurrentLast = order.find(last);
        chk(itCurrentLast != order.end());
        chk(*itCurrentLast == last);
        if(last == mp(cnt, val)) {
            if(itCurrentLast != order.begin()) { //? left
                itCurrentLast--;
                last = *itCurrentLast;
                sum += last.f * last.s;
            } else {
                itCurrentLast++;
                if(itCurrentLast != order.end()) { //? right
                    last = *itCurrentLast;
                    countRight--;
                } else {
                    last = NOTHING;
                    countRight = -79;
                }
            }
            safeErase(order, mp(cnt, val));
            norm();
        } else {
            safeErase(order, mp(cnt, val));
            if(last < mp(cnt, val)) { //? right
                countRight--;
            }
            norm();
        }
    };

    auto addNormal = [&](ll val, ll cnt, bool withInitialization) {
        order.emplace(cnt, val);
        if(withInitialization) {
            last = mp(cnt, val);
            countRight = 1;
            sum += val * cnt;
        }
        hist[val] = cnt;
    };

    auto add = [&](ll val, ll cnt) {
        dbg("add before", val, cnt, order, last, hist, sum, countRight);
        if(hist[val] > 0) {
            delRegistry(val, hist[val]);
        }

        hist[val] += cnt;
        addNormal(val, hist[val], order.empty());
        if(!order.empty()) {
            if(last < mp(hist[val], val)) { //? right
                countRight++;
                sum += val * hist[val];
            }
            norm();
        }
        dbg("add after", val, cnt, order, last, hist, sum, countRight);
    };

    auto del = [&](ll val) {
        dbg("del before", val, hist[val], order, last, hist, sum, countRight);
        {
            auto it = order.find(mp(hist[val], val));
            chk(it != order.end());
        }
        delRegistry(val, hist[val]);
        dbg("del middle", val, hist[val], sum);
        if(hist[val] > 1) {
            ll guarda = hist[val];
            safeErase(hist, val);
            add(val, guarda - 1LL);
        } else hist[val]--;
        dbg("del after", val, order, last, hist, sum, countRight);
    };

    vl ans;
    auto answer = [&]() {
        dbg("ans!", sum);
        ans.eb(sum);
    };

    const int n = sz(nums);
    for(int i = 0; i < k; i++) {
        add(nums[i], 1LL);
    }
    answer();
    dbg(ans);
    for(int i = k; i < n; i++) {
        del(nums[i - k]);
        add(nums[i], 1LL);
        answer();
    }

    return ans;
}

void solve() {
    //? <>
}

mt19937 rng(0);
//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    while(1) {
        RAYA;
        ll n = rng_ll(1, 5);
        ll k = rng_ll(1, n);
        ll x = rng_ll(1, k);
        vi nums(n); each(e, nums) e = rng_ll(1, 10);
        dbg(n, k, x);
        dbg(nums);
        dbg("Brute");
        vl ans = brute(nums, k, x);
        dbg("/Brute");
        dbg("Greedy");
        vl greedy = slv(nums, k, x);
        dbg("/Greedy");
        dbg(ans);
        dbg(greedy);
        chk(ans == greedy); 
    }

    int t = 1; //! cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
