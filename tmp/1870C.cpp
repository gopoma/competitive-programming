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

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

#define mp  make_pair
#define F   first
#define S   second

#define sz(x)   int((x).size())
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

#define lb lower_bound
#define ub upper_bound

const int MOD = (int)1e9 + 7;   // 998244353;
const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

vector<int> farthest_min_right(vector<int>& a) {
    const int n = int(a.size());
    vector<int> res(n);

    // To store minimum element
    // in the range i to n
    vector<int> suffix_min(n);
    suffix_min[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suffix_min[i] = max(suffix_min[i + 1], a[i]);
    }
    // DBG(suffix_min);

    for (int i = 0; i < n; i++) {
        int low = i + 1, high = n - 1, ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;

            // If current element in the suffix_min
            // is less than a[i] then move right
            if (suffix_min[mid] >= a[i]) {
                ans = mid;
                low = mid + 1;
            }
            else
                high = mid - 1;
        }

        res[i] = (ans == -1)? i : ans;
    }

    return res;
}

vector<int> farthest_min_left(vector<int>& a) {
    const int n = int(a.size());
    vector<int> res(n);

    // To store minimum element
    // in the range i to n
    vector<int> prefix_min(n);
    prefix_min[0] = a[0];
    for (int i = 1; i < n; i++) {
        prefix_min[i] = max(prefix_min[i - 1], a[i]);
    }
    // DBG(prefix_min);

    for (int i = 0; i < n; i++) {
        int low = 0, high = i - 1, ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;

            // If current element in the suffix_min
            // is less than a[i] then move left
            if (prefix_min[mid] >= a[i]) {
                ans = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }

        res[i] = (ans == -1)? i : ans;
    }

    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> A(n);

    for(auto& a: A) {
        cin >> a;
    }

    set<int> aux;

    for(auto& a: A) {
        assert(1 <= a && a <= k);
        aux.ins(a);
    }

    vector<int> ans(k + 1, 0);
    vector<int> fminr = farthest_min_right(A);
    vector<int> fminl = farthest_min_left(A);

    for(int i = 0; i < n; i++) {
        // DBG4(A[i], i, fminr[i], fminl[i]);
        ans[A[i]] = max(ans[A[i]], 2 * abs(fminr[i] - fminl[i] + 1));
    }

    for(int i = 1; i <= k; i++) {
        cout << ans[i] << " ";
    }
    cout << n_l;
    // RAYA;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
