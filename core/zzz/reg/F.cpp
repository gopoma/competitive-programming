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

void solve(){
    // <>
	ll a, b, c, d;
    cin >> a >> b >> c >> d;
    dbg(a, b, c, d);

    str A, B, C, D;
    A = to_string(a);
    B = to_string(b);
    C = to_string(c);
    D = to_string(d);

    for(int mask = 0; (mask + 1) < (1 << (sz(A))); mask++) {
        // 1 - deleted
        // 0 - go
        vl deleted_a;
        str ap;
        for(int i = 0; i < sz(A); i++) {
            if(mask & (1 << i)) {
                // 1
                deleted_a.eb(ll(A[i] - '0'));
            } else {
                // 0
                ap.push_back(A[i]);
            }
        }

        RAYA;
        dbg(bitset<10>(mask).to_string(), ap);

        // trailing zeros
        if(ap.empty() || (ap.front() == '0')) {
            dbg("trailing zeros");
            continue;
        }

        // check that b is an integer
        i128 ad = i128(stoll(ap)) * i128(d);
        if((ad % (i128(c))) != 0) {
            dbg("b is not an integer");
            continue;
        }

        // check that b is lower than 1e18
        i128 bpn = ad / (i128(c));
        if(bpn > i128(BIG)) {
            dbg("b is already bigger than BIG");
            continue;
        }

        str bp = to_string(ll(bpn));
        dbg(A, ap, B, bp);

        // check that bp is a subsequence of B
        auto [ok, ids] = isSub(B, bp);
        if(!ok) {
            dbg("bp is not a subsequence of B");
            continue;
        }

        // check that the multiset of deleted from a is the same as the multiset of deleted from b
        set<int> taken;
        for(auto& id: ids) taken.emplace(id);

        vl deleted_b;
        for(int i = 0; i < sz(B); i++) {
            if(taken.count(i)) {

            } else {
                deleted_b.emplace_back(ll(B[i] - '0'));
            }
        }

        sort(all(deleted_a));
        sort(all(deleted_b));

        if(deleted_a == deleted_b) {
            cout << "possible\n";
            cout << ap << " " << bp << "\n";
            return;
        } else {
            dbg("multisets of deleted elements doesn't match");
        }
    }
    cout << "impossible\n";
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
