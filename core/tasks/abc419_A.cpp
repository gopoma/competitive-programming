#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    map<string, string> mp;
    mp["red"] = "SSS";
    mp["blue"] = "FFF";
    mp["green"] = "MMM";
    string S; cin >> S;
    if(mp.count(S)) cout << mp[S] << "\n";
    else cout << "Unknown\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
