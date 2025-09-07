#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;
using str = string;

using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
mt19937 rng(0);

ll rng_ll(ll L, ll R) {
    assert(L <= R);
    return uniform_int_distribution<ll>(L, R)(rng);
}

template<class T> void shuf(vector<T>& v) {
    shuffle(all(v), rng);
}


#define dbg(x) cout << #x << ": " << x << endl
#define dbg(x) 0
#define RAYA dbg("===========================")
template<class T> void pvec(vector<T> v) {
}

class MEX {
  struct MEXNode {
    MEXNode *children[2];
    bool is_full = false;
    int cnt = 0;

  public:
    MEXNode() {
      children[0] = nullptr;
      children[1] = nullptr;
    }
  };
private:

  inline MEXNode *nonnull(MEXNode *& n) {
    if (!n) n = new MEXNode();
    return n;
  }

  void insert(int val, int level, MEXNode *n) {
    if (level == -1) {
      n->cnt++;
      n->is_full = true;
      return;
    }

    int cur_bit = (val & (1 << level)) >> level;
    insert(val, level - 1, nonnull(n->children[cur_bit]));

    n->is_full = nonnull(n->children[0])->is_full && nonnull(n->children[1])->is_full;
    n->cnt = nonnull(n->children[0])->cnt + nonnull(n->children[1])->cnt;
  }

  // Remove an integer from the set
  void remove(int val, int level, MEXNode *n) {
    if (level == -1) {
      n->cnt--;
      n->is_full = n->cnt > 0;
      return;
    }

    int cur_bit = (val & (1 << level)) >> level;
    remove(val, level - 1, nonnull(n->children[cur_bit]));

    n->is_full = nonnull(n->children[0])->is_full && nonnull(n->children[1])->is_full;
    n->cnt = nonnull(n->children[0])->cnt + nonnull(n->children[1])->cnt;
  }

  // Find the minimum element >=x that isn't present in the set
  int get(int val, int level, MEXNode *n) {
    if (n->is_full) {
      return -1;
    } else if (n->cnt == 0) {
      return val;
    }

    int cur_bit = (val & (1 << level)) >> level;
    int ans = get(val, level - 1, nonnull(n->children[cur_bit]));
    if (cur_bit == 0 && ans == -1) {
      ans = get((val >> level << level) | (1 << level), level - 1, nonnull(n->children[1]));
    }

    return ans;
  }

  MEXNode root_node;
public:

  void insert(int x) {
    insert(x, 31, &root_node);
  }
  void remove(int x) {
    remove(x, 31, &root_node);
  }
  int get(int x) {
    return get(x, 31, &root_node);
  }
};

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n); for(auto& x: a) cin >> x;
    sort(a.begin(), a.end());

    map<ll, ll> hist;
    for(auto& x: a) hist[x]++;

    for(ll mex = 0; mex <= n; mex++) {
        if(hist[mex] == 1) {

        } else {
            break;
        }
    }


    map<vl, bool> vis;
    vector<vl> history;
    while(!vis[a]) {
        history.emplace_back(a);
        vis[a] = true;

        MEX mex;
        for(auto& x: a) mex.insert(x);

        vl b(n);
        for(int i = 0; i < n; i++) {
            mex.remove(a[i]);
            b[i] = mex.get(0);
            mex.insert(a[i]);
        }
        a = b;
    }

    dbg("his");
    for(auto& vec: history) {
        pvec(vec);
    }
    dbg("a:");
    pvec(a);

    ll cnt = 0;
    vector<vector<ll>> cyc;
    for(int j = sz(history) - 1; j >= 0; j--) {
        cyc.emplace_back(history[j]);
        cnt++;
        if(history[j] == a) {
            break;
        }
    }
    reverse(all(cyc));
    dbg(cnt);

    ll tail = sz(history) - cnt;

    if(k < tail) {
        dbg("tail");
        ll re = accumulate(all(history[k]), 0LL);
        cout << re << "\n";
        return;
    } else {
        k -= tail;
    }

    dbg("history");
    for(auto& vec: history) {
        pvec(vec);
    }


    dbg("cyc");
    for(auto& vec: cyc) {
        pvec(vec);
    }
    dbg(k);
    dbg(tail);

    k %= sz(cyc);
    ll re = accumulate(all(cyc[k]), 0LL);
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--) {
        RAYA;
        solve();
    }

    return 0;
}
