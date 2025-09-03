#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#define int long long

#define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0
#define RAYA   dbg("========================");

int brute(ll n, string S) {
    auto check = [&](string xd) -> int {
        for(int i = 1; i < n; i++) {
            if(xd[i] == xd[i - 1]) return false;
        }
        return true;
    };

    map<string, bool> vis; vis[S] = true;
    map<string, int> dist; dist[S] = 0;
    deque<string> q; q.emplace_back(S);

    while(!q.empty()) {
        auto cur = q.front(); q.pop_front();
        if(check(cur)) {
            return dist[cur];
        }
        for(int i = 0; i + 1 < n; i++) {
            string nxt = cur;
            swap(nxt[i], nxt[i + 1]);
            if(!vis[nxt]) {
                vis[nxt] = true;
                dist[nxt] = dist[cur] + 1;
                q.emplace_back(nxt);
            }
        }
    }
    assert(false);
}

int slv(ll n, string S) {
    auto work = [&](string tar) -> int {
        string Stemp = S;
        dbg(tar);
        set<int> A, B;
        for(int i = 0; i < n; i++) {
            if(S[i] == 'A') A.emplace(i);
            else B.emplace(i);
        }

        int re = 0;
        for(int i = 0; i < n; i++) {
            if(tar[i] == 'A') {
                if(S[i] == tar[i]) {
                } else {
                    auto it = A.lower_bound(i);
                    int id = *it;

                    assert(it != A.end());
                    re += (id) - i;

                    swap(S[i], S[id]);
                    A.erase(id);
                    A.emplace(i);
                    B.erase(i);
                    B.emplace(id);
                }
            } else {
                if(S[i] == tar[i]) {
                } else {
                    auto it = B.lower_bound(i);

                    assert(it != B.end());
                    re += (*it) - i;

                    swap(S[i], S[*it]);
                    B.erase(*it);
                    B.emplace(i);
                    A.erase(i);
                    A.emplace(*it);
                }
            }
        }
        S = Stemp;
        return re;
    };

    string ab, ba;
    string base = "AB";
    int cur = 0;
    for(int i = 0; i < n; i++) {
        ab.push_back(base[(cur) % 2]);
        ba.push_back(base[(cur + 1) % 2]);
        cur++;
    }

    int re = min(work(ab), work(ba));
    return re;
}

void solve() {
    int n; cin >> n;
    string S; cin >> S;
    n *= 2;
    int re = slv(n, S);
    cout << re << "\n";
}

mt19937 rng(0); // or mt19937_64

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }


signed main() {
    ios_base::sync_with_stdio(false);

    while(0) {
        RAYA;
        RAYA;
        RAYA;
        int n = rng_ll(1, 10);
        vector<int> p;
        for(int i = 0; i < n; i++) p.emplace_back(0);
        for(int i = 0; i < n; i++) p.emplace_back(1);
        n *= 2;
        string S;
        for(int i = 0; i < n; i++) {
            if(p[i] == 0) S.push_back('A');
            else S.push_back('B');
        }
        dbg(n);
        dbg(S);
        int ans = brute(n, S);
        int gre = slv(n, S);
        dbg(ans);
        dbg(gre);

        assert(ans == gre);
    }

    solve();

    return 0;
}

