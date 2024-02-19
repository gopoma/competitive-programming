#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

void brute() {
    map<int, char> go;
    go[0] = 'L';

    auto check = [](int xx) {
        string S = to_string(xx);
        const int n = int(S.size());

        for(int i = 0; i < n / 2; i++) {
            if(S[i] != S[n - i - 1]) {
                return false;
            }
        }
        return true;
    };

    vector<int> can;
    const int MAXN = 1e5;
    for(int x = 1; x <= MAXN; x++) {
        if(check(x)) can.emplace_back(x);

        bool ok = false;

        for(auto& val: can) {
            assert(x - val >= 0);

            if(go[x - val] == 'L') {
                go[x] = 'W';
                ok = true;
                break;
            }
        }

        if(!ok) {
            go[x] = 'L';
        }
    }

    for(int x = 1; x <= MAXN; x++) {
        if(go[x] == 'L') assert(x % 10 == 0);
    }
}

void solve() {
    string S; cin >> S;

    bool win = S.back() != '0';
    if(win) cout << "B";
    else cout << "E";
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        solve();
    }
}
