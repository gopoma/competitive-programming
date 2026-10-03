#pragma GCC optimize ("Ofast")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x)
#define RAYA dbg("================================")

// Strategy: count amount of 2's in x!
void solve() {
    int n; cin >> n;
    vector<ll> a(n); for(auto& x: a) cin >> x;

    vector<ll> dp(n + 1);
    dp[0] = 0;
    for(int x = 1; x <= n; x++) {
        int cur = x;
        while(cur % 2 == 0) {
            dp[x]++;
            cur /= 2;
        }
        dp[x] += dp[x - 1];
    }

    ll re = 0;
    for(int i = 0; i < n; i++) {
        RAYA;
        // C(n - 1, i) mod 2
        ll A = dp[n - 1];
        ll B = dp[i];
        ll C = dp[(n - 1) - i];

        ll cnt = A - (B + C);
        dbg(i);
        dbg(A);
        dbg(B);
        dbg(C);
        if(cnt == 0) {
            re ^= a[i];
        } else {

        }
    }
    cout << re << "\n";
}



//* Template
namespace exlucas
{
	typedef long long ll;
	typedef pair<int,int> pa;
	int P,p,q,i;
	vector<pa> a;
	vector<vector<int> > b;
	vector<int> ph;
	vector<int> xs;
	int ksm(unsigned int x,ll y,const unsigned int p)
	{
		unsigned int r=1;
		while (y)
		{
			if (y&1) r=(unsigned long long)r*x%p;
			x=(unsigned long long)x*x%p;
			y>>=1;
		}
		return r;
	}
	void init(int x)//分解质因数，如有必要可以使用更快的方法
	{
		a.clear();b.clear();
		int i,y,z;
		vector<int> v;
		for (i=2;i*i<=x;i++) if (x%i==0)
		{
			z=i;x/=i;
			while (1)
			{
				y=x/i;
				if (i*y==x) x=y; else break;
				z*=i;
			}
			a.push_back(pa(i,z));
			b.push_back(v);
		}
		if (x>1) a.push_back(pa(x,x)),b.push_back(v);
		ph.resize(a.size());
		xs.resize(a.size());
		for (int k=0;k<a.size();k++)
		{
			tie(q,p)=a[k];
			ph[k]=p/q*(q-1);
			xs[k]=(ll)ksm(P/p,ph[k]-1,p)*(P/p)%P;
		}
	}
	void spinit(int x)//O(p) space
	{
		for (int k=0;k<a.size();k++)
		{
			int q,p;
			tie(q,p)=a[k];
			b[k].resize(p);
			b[k][0]=1;
			for (int i=1,j=q;i<p;i++) if (i==j) j+=q,b[k][i]=b[k][i-1]; else b[k][i]=(ll)b[k][i-1]*i%p;
		}
	}
	ll g(ll n)
	{
		ll r=0,s;
		while (n>=q)
		{
			n/=q;
			r+=n;
		}
		return r;
	}
	// int f(ll n)
	// {
	// 	if (n==0) return 1;
	// 	int r=1;//若 p>1e9 j 要 unsigned
	// 	for (int i=1,j=q;i<p;i++) if (i==j) j+=q; else r=(ll)r*i%p;
	// 	r=(ll)ksm(r,n/p,p)*f(n/q)%p;
	// 	n%=p;
	// 	for (int i=1,j=q;i<=n;i++) if (i==j) j+=q; else r=(ll)r*i%p;
	// 	return r;
	// }//O(T\sum p) time,O(1) space ver.
	int f(ll n)
	{
		int r=1;
		ll cs=0;
		while (n)
		{
			r=(ll)r*b[i][n%p]%p;
			cs+=n/p;
			n/=q;
		}
		return (ll)ksm(b[i][p-1],cs%ph[i],p)*r%p;
	}//O(\sum p) time,O(p) space ver.
	int C(ll n,ll m,int M)
	{
		int r=0,w;
		if (P!=M) init(P=M),spinit(P);//sp for O(p) space
		for (i=0;i<a.size();i++)
		{
			tie(q,p)=a[i];
			w=(ll)ksm(q,g(n)-g(m)-g(n-m),p)*f(n)%p*ksm((ll)f(m)*f(n-m)%p,ph[i]-1,p)%p;
			r=(r+(ll)xs[i]*w)%M;
		}
		return r;
	}
}
#define C(x,y,z) exlucas::C(x,y,z)
//* /Template

// Strategy: calculate C(n - 1, i) mod 2 using exlucas
void solve2() {
    int n; cin >> n;
    vector<ll> a(n); for(auto& x: a) cin >> x;

    ll re = 0;
    for(int i = 0; i < n; i++) {
        ll cur = C(n - 1, i, 2);
        if(cur == 1) {
            re ^= a[i];
        }
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve2();

    return 0;
}
