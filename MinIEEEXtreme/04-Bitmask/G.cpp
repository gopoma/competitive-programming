#include <bits/stdc++.h>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < int(v.size()); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

signed main() {
    int n;
    cin >> n;

    int k;
    cin >> k;

    vector<int> b(k);
    for(auto& e: b) {
        cin >> e;
    }

    for(int x = 0; x < (1<<k); x++) {
        vector<int> subset;
        for(int i = 0; i < k; i++) {
            if(x&(1<<i)) subset.push_back(b[i]);
        }

        int count = 0;
        for(auto& e: subset) {
            count += pow(2, e);
        }

        cout << count << ": ";
        for(auto& e: subset) {
            cout << e << " ";
        }
        cout << "\n";
    }

    return 0;
}
