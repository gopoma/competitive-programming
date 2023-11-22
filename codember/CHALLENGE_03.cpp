#include <bits/stdc++.h>

using namespace std;

signed main() {
    freopen("CHALLENGE_03.in", "r", stdin);
    freopen("CHALLENGE_03.out", "w", stdout);

    int mn; char pad; int mx;
    char c, pad2; string password;

    vector<string> bads;
    while(cin >> mn >> pad >> mx >> c >> pad2 >> password) {
        map<char, int> cnt;
        for(auto& x: password) cnt[x]++;

        if(!(mn <= cnt[c] && cnt[c] <= mx)) bads.emplace_back(password);
    }

    cout << bads[41] << "\n";
}
