#include <bits/stdc++.h>
using namespace std;
string to_string (string s){
    return '"' + s + '"';
}
string to_string(const char*s){
    return to_string((string) s);
}
string to_string(char c){
    return string(1,c);
}
string to_string(bool b){
    return b ? "true" : "false";
}
template <typename A>
string to_string(A v);
template <typename A , typename B>
string to_string(pair<A,B> p){
    return "(" + to_string(p.first) + " , " + to_string(p.second) + ")";
}
template <typename A>
string to_string(A v){
    bool first=true;
    string res="[";
    for(const auto & x : v){
        if(!first) res +=", ";
        first=false;
        res+=to_string(x);
    }
    res+="]";
    return res;
}
void debug_out(){
    cerr<<endl;
}
template <typename Head,typename...Tail>
void debug_out(Head H,Tail... T){
    cerr<<" "<<to_string(H);
    debug_out(T...);
}
#ifdef LOCAL
#define MACRO(code) do{code}while(false)
#define dbg(x){auto xd = x; cout<<"Line (:"<<__LINE__<<"):"<<"\033[1;34m"<<#x<<"\033[0;32m = \033[35m"<<to_string(xd)<<"\033[0m"<<endl;}
#define dbg(...) MACRO(cout<<"Line(" <<__LINE__<<"): "<<"\033[1;34m" <<"[" <<#__VA_ARGS__<<"]\033[35m:"; debug_out(__VA_ARGS__); cout<<"\033[0m";)

#define GA dbg(0)
#define RAYA cout<<"\033[101m"<<"=============="<<"\033[0m"<<end;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
using ll = long long;
using db = long double;
using str = string;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template <class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;

#define sz(x) int((x).size())
#define all(x) begin(x) , end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for(int i = (a) ; i < (b) ; ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for(int i = (b)-1;i>=(a);--i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for(auto & a : x)

const int MOD = 1e9 + 7;
const db PI = acos((db)-1);
//mt19937 rng(0);
mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
tcT> bool ckmin(T&a, const T&b){
    return b < a ? a=b,1:0;
}
tcT> bool ckmax(T&a, const T&b){
    return a < b ? a=b,1:0;
}
void setIn(string s){
    freopen(s.c_str(),"r",stdin);
}
int rng_int(int L,int R){assert(L<=R);
return uniform_int_distribution<int>(L,R)(rng);}
ll rng_ll(ll L,ll R){assert(L<=R);
return uniform_int_distribution<ll>(L,R)(rng);}


using i128 = __int128;
std::ostream& operator<<(std::ostream& o, const __int128& x) {
    if (x == std::numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << (x / i128(10)) << (char)(x % 10 + '0');
}

//* here goes the template!
const int MAX = int(1e6) + 12; // TODO: SQRT3

long long n;
vector<int> primes;
bool composite[MAX];
vector<long long> divisors;
vector<pair<long long, int>> factors;

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]) primes.emplace_back(i);
		for(int p : primes){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			if(i % p == 0) break;
		}
	}
}

void backtracking(int pos, long long val){
	if(pos == factors.size()){
		divisors.emplace_back(val);
		return;
	}
	long long p = 1;
	for(int i = 0; i <= factors[pos].second; i++){
		backtracking(pos + 1, val * p);
		p *= factors[pos].first;
	}
}

bool has_square_root(long long n){
	int r = round(sqrt(n));
	return 1ll * r * r == n;
}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = mod_mul(ans, b, mod);
	return ans;
}

bool miller_rabin(ull n){
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for(auto a : A) {   // ^ count trailing zeroes
		ull p = mod_pow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = mod_mul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull pollard_rho(ull n) {
	auto f = [n](ull x) { return mod_mul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = mod_mul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}

void factorize(){
	for(int p : primes){
		if(p * p * p > n) break;
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		if(e) factors.emplace_back(make_pair(p, e));
	}
	if(miller_rabin(n)){
		factors.emplace_back(make_pair(n, 1));
	}
	else if(has_square_root(n)){
		factors.emplace_back(make_pair((long long)round(sqrt(n)), 2));
	}
	else{
		long long d = pollard_rho(n);
		factors.emplace_back(make_pair(d, 1));
		factors.emplace_back(make_pair(n / d, 1));
	}
	backtracking(0, 1);
}
//* /here goes the template!

const char n_l = '\n';

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}

// TODO: modularize >:v
vector<long long> factorize(long long x) {
    divisors.clear();
    factors.clear();

    n = x;

    factorize();
    dbg(divisors);
    remDup(divisors);

    return divisors;
}

void solve(){
    // <>
    ll n;
    cin >> n;
    vl a(n);
    for (auto& e : a) cin >> e;
    sort(all(a));

    if(n == 1) {
        if(a[0] == 1) {
            cout << "*\n";
        } else {
            cout << a[0] << " 1\n";
        }
        return;
    }

    if(a[0] != 1) {
        cout << a[n - 1] << " 1\n";
        return;
    }

    dbg(n, a);
    vl divs = factorize(a[n - 1]);
    dbg(divs);

    if(sz(divs) == n + 1) {
        set<ll> aux;
        for(auto& x: a) aux.emplace(x);
        for(auto& x: divs) {
            if(!aux.count(x)) {
                cout << a[n - 1] << " " << x << "\n";
                return;
            }
        }
        assert(false);
    } else {
        i128 X = i128(a[1]) * i128(a[n - 1]);
        cout << X << " " << X << "\n";
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    ll t=1;
    init();
    //cin>>t;
    while(t--) solve();
    return 0;
}
