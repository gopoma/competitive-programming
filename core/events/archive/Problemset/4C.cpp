#include <iostream>
#include <map>
#include <string>

using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    map<string, ll> names;

    for(ll i = 0; i < n; i++) {
        string s;
        cin >> s;

        if(names[s] == 0) {
            cout << "OK";
            names[s] = 1;
        } else {
            cout << (s + to_string(names[s]));
            names[s]++;
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
