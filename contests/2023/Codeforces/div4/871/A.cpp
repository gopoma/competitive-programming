#include <iostream>

using namespace std;

using ll = long long;

void solve() {
    string base = "codeforces";
    string s;
    cin >> s;

    int counter = 0;

    for(int i = 0; i < s.size(); i++) {
        if(s[i] != base[i]) {
            counter++;
        }
    }

    cout << counter << endl;
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
