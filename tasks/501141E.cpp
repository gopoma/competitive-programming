#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map <ll,ll> mll;
typedef vector <pair<ll,ll>> vpll;
typedef priority_queue<ll> pq;
#define FOR(i, a, b) for (long long i=a; i<(b); i++)
#define FOR1(i, a, b) for (long long i=a; i<=(b); i++)
#define mp make_pair
#define pb push_back
#define f first
#define se second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif

const int MOD = 1000000007;
const char nl = '\n';
const int MX = 15;
const int N=1000+3;
bool check(ll a,ll b,ll n){
	return ((a+b)^n)==(a^(b+n)^n);
}
tuple<ll, ll, ll> solve(ll n){
    if(n%2==1){
        return make_tuple(-1, 0, 0);
    }
    else{
    	ll a=n/2;
    	ll b=0;
    	ll signi=0;
    	for(int i=60;i>=0;i--){
    		ll act=1ll<<i;
    		if(act&n){
    			signi=i;
    			break;
    		}
    	}
    	FOR(i,0,signi){
    		ll act=(1ll<<(i));
    		if(act&n){

    		}
    		else{
    			b+=act;
    		}
    	}
    	if(!check(a,b,n)){
    		cout<<"f\n";
    	}
        return make_tuple(1, a, b);
    }

}

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
//* here goes the template!
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//* /here goes the template!

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t=1;

    while(1) {
        ll n = rng_ll(2LL, 1LL << 60LL - 1LL);


        if(n % 2 == 0) {
            auto ans = solve(n);
            ll a = get<1>(ans);
            ll b = get<2>(ans);
            if(check(a, b, n)) {
                dbg("go", a, b, n);
            } else {
                dbg("jaaa", a, b, n);
                exit(0);
            }
        }
    }

    return 0;
}
