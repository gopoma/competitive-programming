#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

template <typename T>
ostream& operator <<(ostream& os, const vector<T>& v) {
    os << "[";
    forn(i,v.size())
    {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

template <typename T>
istream& operator >>(istream& is, vector<T>& v) {
    int n;
    is >> n;
    v.resize(n);
    forn(i,n)
        is >> v[i];
    return is;
}



const char nl = '\n';

bool sortbyCond(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first)
        return (a.first < b.first);
    else
       return (a.second > b.second);
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for(auto& e: v) {
        cin >> e.first;
        cin >> e.second;
    }

    sort(ALL(v), sortbyCond);

    set<int> a;
    for(auto& e: v) {
        a.insert(e.first);
    }

    int go = v[0].first, counter = 0;
    ll result = 0;

    for(auto& e: v) {
        if(e.first == go) {
            if(counter < go) {
                result += e.second;
                counter++;
            } else {
                a.erase(go);
                if(SIZE(a) == 0) break;
                go = *a.begin();
                counter = 0;
            }
        } else if(e.first > go) {
            result += e.second;
            a.erase(go);
            if(SIZE(a) == 0) break;
            go = *a.begin();
            counter = 1;
        }
    }

    cout << result << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
