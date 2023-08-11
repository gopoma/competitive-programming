#include <iostream>
#include <set>

using namespace std;

using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;

    if(n < m) {
        cout << "NO" << endl;
        return;
    }
    
    set<ll> tmp;
    tmp.insert(n);

    bool isFound = false;
    while(!isFound) {
        if(tmp.count(m)) {
            isFound = true;
            continue;
        }

        int prevSize = tmp.size();

        for(ll ee: tmp) {
            if(ee % 3 == 0) {
                tmp.insert(ee / 3);
                tmp.insert(2 * (ee / 3));
            }
        }

        if(prevSize == tmp.size()) {
            break;
        }
    }

    if(isFound) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
