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

#define F first
#define S second
#define SIZE(c) ll((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

// Direction vectors
ll dRow[4] = { -1, 0, 1,  0 };
ll dCol[4] = {  0, 1, 0, -1 };

bool inBounds(ll x, ll y, ll boundx, ll boundy) {
    return x >= 0 && y >= 0 && x < boundx && y < boundy;
}

void solve() {
    ll n;
    cin >> n;

    string g1[n][n], g2[n][n];

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            char a, b; cin >> a >> b;
            g1[i][j] = a; // A-Z
            g2[i][j] = b; // 1-n
        }
    }

    // cout << "g1:\n";
    // for(ll i = 0; i < n; i++) {
    //     for(ll j = 0; j < n; j++) {
    //         cout << g1[i][j] << " ";
    //     }
    //     cout << nl;
    // }

    // cout << "g2:\n";
    // for(ll i = 0; i < n; i++) {
    //     for(ll j = 0; j < n; j++) {
    //         cout << g2[i][j] << " ";
    //     }
    //     cout << nl;
    // }

    bool vis[n][n];
    for(ll i = 0; i < n; i++)
        for(ll j = 0; j < n; j++)
            vis[i][j] = false;

    queue<pair<ll, ll>> q;
    unordered_map<string, ll> resultados;

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++)  {
            if(!vis[i][j]) {
                q.push({i, j});
                vis[i][j] = true;

                string c = g1[i][j];
                ll counter = 0;
                while(!q.empty()) {
                    pair<ll, ll> cell = q.front();
                    ll x = cell.first;
                    ll y = cell.second;

                    q.pop();

                    // Process
                    counter++;

                    for(ll k = 0; k < 4; k++) {
                        ll adjx = x + dRow[k];
                        ll adjy = y + dCol[k];

                        bool isCandidate = inBounds(adjx, adjy, n, n) && !vis[adjx][adjy] && g1[adjx][adjy] == c;
                        if(isCandidate) {
                            q.push({ adjx, adjy });
                            vis[adjx][adjy] = true;
                        }
                    }
                }
                resultados[c] = max(resultados[c], counter);
            }
        }
    }
    ll score1 = 0;
    for(auto& it: resultados) {
        score1 += (((it.S)-1)*(it.S))/2;
    }




    for(ll i = 0; i < n; i++)
        for(ll j = 0; j < n; j++)
            vis[i][j] = false;

    vector<ll> scoring2(30, 0);
    queue<pair<ll, ll>> qqq;
    unordered_map<string, ll> resultados2;

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            if(!vis[i][j]) {
                qqq.push({i, j});
                vis[i][j] = true;

                string c = g2[i][j];
                ll counter = 0;
                while(!qqq.empty()) {
                    pair<ll, ll> cell = qqq.front();
                    ll x = cell.first;
                    ll y = cell.second;

                    qqq.pop();

                    // Process
                    counter++;

                    for(ll k = 0; k < 4; k++) {
                        ll adjx = x + dRow[k];
                        ll adjy = y + dCol[k];

                        bool isCandidate = inBounds(adjx, adjy, n, n) && !vis[adjx][adjy] && g2[adjx][adjy] == c;
                        if(isCandidate) {
                            qqq.push({ adjx, adjy });
                            vis[adjx][adjy] = true;
                        }
                    }
                }
                resultados2[c] = max(resultados2[c], counter);
            }
        }
    }

    ll score2 = 0;
    for(auto& it: resultados2) {
        score2 += (((it.S)-1)*(it.S))/2;
    }
    cout << score1 << " " << score2 << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
