
#pragma GCC optimize ("trapv")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;
using str =string;
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;
using ull= unsigned long long;
string to_string(string s){
    return '"' + s + '"';
}
string to_string(const char* s){
    return to_string((string) s);
}

string to_string(char c){
    return string(1,c);
}
string to_string(bool b){
    return ( b ? "true" : "false");
}
template<typename A>
string to_string(A v);
string to_string(vector<bool> v){
    bool first=true;
    string res="[";
    for(auto  x : v){
        if(!first){
            res+=", ";
        }
        first=false;
        res+=x ? "true" : "false";
    }
    res+="]";
    return res;
}
template<typename A,typename B>
string to_string(pair<A,B> p){
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template<typename A>
string to_string(A v){
    bool first=true;
    string res="[";
    for(const auto &x : v){
        if(!first){
            res+=", ";
        }
        first=false;
        res+=to_string(x);
    }
    res+="]";
    return res;
}
void debug_out(){cerr<<endl;}
template < typename Head,typename...Tail>
void debug_out(Head H,Tail... T){
    cerr<<" "<<to_string(H);
    debug_out(T...);
}
#ifdef LOCAL
const vector<string> __C_DBG{"\033[1;34m" , "\033[0;32m = \033[35m" , "\033[0m" , "]\033[35m:" , "\033[101m" , "\033[0m" };

#define MACRO(code) do{code}while(false)
#define dbg(x) {auto xd = x; cout<<"Line("<<__LINE__<<"): "<<__C_DBG[0] << #x << __C_DBG[1] << to_string(xd)<<__C_DBG[2]<<endl;}
#define dbg(...) MACRO(cout<<"Line("<<__LINE__<<"): "<<__C_DBG[0] << "[" <<#__VA_ARGS__ << __C_DBG[3]; debug_out(__VA_ARGS__); cout<<__C_DBG[2];  )
#define GA dbg(0)
#define RAYA MACRO(cerr<<__C_DBG[4] << "================================"<<__C_DBG[5] << endl;)
const bool isDebugging=true;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
const bool isDebuging=false;

#endif

using pi=pair<int,int>;
using pl = pair<ll,ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT,size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl=V<ll>;
using vb=V<bool>;
using vpi=V<pi>;
using vpl = V<pl>;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
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
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)
#define F0R(i,a) FOR(i,0,a)

#define ROF(i,a,b) for(ll i=(b)-1;i>=(a);--i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for(auto & a : x)
const int MOD=1e9+7;
const int INF=int(1e9)+5;
const ll BIG=ll(1e18)+5;
const db PI = acos((db)-1);
mt19937 rng(0);
//mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
ll cdiv(ll a,ll b){
    return a/b + ((a^b) >0 && a%b);
}
ll fdiv(ll a,ll b){
    return a/b - ((a^b)  < 0 && a%b);
}
tcT> bool ckmin(T& a, const T& b){
    return b < a ? a = b , 1: 0;
}
tcT> bool ckmax(T& a, const T& b){
    return a < b ? a = b , 1: 0;
}
tcT> void remDup(vector<T> &v){
    sort(all(v));
    v.erase(unique(all(v)),end(v));
}
void setIn(string s){
    freopen(s.c_str(),"r",stdin);
}
void setOut(string s){
    freopen(s.c_str(),"w",stdout);
}

vector<int> dx{-1,  0,  0, +1};
vector<int> dy{ 0, -1, +1,  0};

using i128 = __int128;

// check that B is a subsequence of A
pair<bool, vi> isSub(str A, str B) {
    const int n = sz(A);
    const int m = sz(B);

    vi ids;
    int j = 0;
    for(int i = 0; i < n; i++) {
        if(j == m) break;
        if(A[i] == B[j]) {
            ids.emplace_back(i);
            j++;
        } else {

        }
    }

    if(j == m) return {true, ids};
    else return {false, ids};
}


i128 __abs(i128 x) {
    if(x < i128(0)) return -x;
    return x;
}

i128 gcd(i128 a, i128 b, i128& x, i128& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(i128 a, i128 b, i128 c, i128 &x0, i128 &y0, i128 &g) {
    g = gcd(__abs(a), __abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void solve(){
	ll n, q;
	cin >> n >> q;

	V<pl> info(n+1);
	info[0] = {1, 0};
	V<pl> queries;


	for (ll i = 1; i <= q; ++i) {
		char c;
		ll x;
		cin >> c >> x;
		info[i] = info[i-1];

		if (c == '+') {
			info[i].second += x;
			info[i].second %= n;
		} else if (c == '*') {
			info[i].first *= x;
			info[i].first %= n;

			info[i].second *= x;
			info[i].second %= n;
		} else {
			queries.emplace_back(i, x);
		}
	}
	map<ll, vl> mp1;
	for (ll i = 0; i < n; ++i) mp1[0].push_back(i);

    dbg(mp1[0]);
	ll last = 1;
	for (ll i = 1; i <= q; ++i) {
		auto [a, b] = info[i];
		ll g = gcd(n, a);

		if (g > last) {
			auto it = mp1.end();
			it--;

			auto& ve1 = it->second;

			vl prev(n, -1);
			auto [a1, b1] = info[i-1];
			for (ll j = 0; j < n; ++j) {
				prev[(j*a1 + b1) % n] = ve1[j];
			}

            dbg(prev);

			V<pl> cur(n, {INF, -1});
			// calculo que numero queda aqui
			for (ll j = 0; j < n; ++j) {
                ll num = prev[j];
                if (num == -1) continue;

				ll nex_pos = (num*a + b) % n;
				ll dist = (nex_pos+n - j) %n;
                dbg(num, j, nex_pos, dist);

				if (cur[nex_pos].first > dist) {
					cur[nex_pos].first = dist;
					cur[nex_pos].second = num;
				}
			}

            dbg(cur);
			mp1[i] = ve1;
			for (ll j = 0; j < n; ++j) {
				mp1[i][j] = cur[(j*a + b) % n].second;
			}

            dbg(i, mp1[i]);
		}

		last = g;
	}

	for (auto [ind, x] : queries) {
        RAYA;
		auto [a, b] = info[ind];
		i128 temp_pos = 0;
        ll pos = 0;

        dbg(a, n, x, b, x - b);
        i128 X, Y, G;
        if (!find_any_solution(a, n, x - b, X, Y, G)) {
            pos = -1;
        } else {
            dbg(ll(X), ll(Y), ll(G));
            temp_pos = X;

            dbg(ll(temp_pos));
            // <>
            i128 step = n / gcd(a, n);
            if(temp_pos < i128(0)) {
                i128 steps = (-temp_pos + step - 1) / step;
                temp_pos += step * steps;
            } else if(temp_pos >= i128(n)) {
                i128 steps = ((temp_pos - n) / step) + 1;
                dbg(ll(pos), ll(steps), ll(step));
                temp_pos -= step * steps;
            }

            if(i128(0) <= temp_pos && temp_pos < i128(n)) {
                pos = ll(temp_pos);
                assert(0 <= pos && pos < n);
            } else {
                pos = -1;
            }
        }

        dbg("after", pos);
		if (pos == -1) {
            cout << -1 << "\n";
		} else {
			auto it = mp1.lower_bound(ind);
			it--;

            dbg(it->first);
			auto& ve = it->second;
			ll res = ve[pos];
            dbg(ve);
			if (res == 0) res = n;
			cout << res << "\n";
		}
	}
}

int main(){
    int t = 1;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        solve();
    }
    return 0;
}
