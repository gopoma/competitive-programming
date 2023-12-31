#include <bits/stdc++.h>

using namespace std;

signed main() {
    freopen("CHALLENGE_01.in", "r", stdin);
    freopen("CHALLENGE_01.out", "w", stdout);

    unordered_map<string, int> cnt;
    unordered_map<string, bool> already;
    vector<string> order;

    string token;
    while(cin >> token) {
        transform(token.begin(), token.end(), token.begin(), ::tolower);

        if(!already[token]) {
            order.emplace_back(token);
            already[token] = true;
        }
        cnt[token]++;
    }

    for(string& word: order) {
        cout << word << cnt[word];
    }
    cout << "\n";
}
