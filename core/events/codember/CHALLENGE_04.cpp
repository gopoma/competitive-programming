#include <bits/stdc++.h>

using namespace std;

signed main() {
    freopen("CHALLENGE_04.in", "r", stdin);
    freopen("CHALLENGE_04.out", "w", stdout);

    auto tokenize = [](string line, string separator) {
        // DBG(line);
        vector<string> tokens;
        while(true) {
            string token = line.substr(0, line.find(separator));
            tokens.emplace_back(token);

            if(line.find(separator) == string::npos) {
                break;
            }
            line = line.substr(line.find(separator) + 1, int(line.size()) - line.find(separator) + 1);
        }
        return tokens;
    };

    string line;
    vector<pair<string, string>> goods;
    vector<pair<string, string>> bads;
    while(cin >> line) {
        vector<string> tokens = tokenize(line, "-");
        assert(tokens.size() == 2);

        string S = tokens[0];
        string checksum = tokens[1];

        map<char, int> cnt;
        for(auto& x: S) cnt[x]++;

        string rchecksum = "";
        for(auto& x: S)
            if(cnt[x] == 1)
                rchecksum += x;

        if(rchecksum == checksum) goods.emplace_back(make_pair(tokens[0], tokens[1]));
        else bads.emplace_back(make_pair(tokens[0], tokens[1]));
    }

    cout << goods[32].second << "\n";
}
