#include <bits/stdc++.h>

using namespace std;

vector<string> tokenize(string line, string separator) {
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

signed main() {
    freopen("CHALLENGE_05.in", "r", stdin);
    freopen("CHALLENGE_05.out", "w", stdout);

    string line;
    vector<string> bads;

    while(getline(cin, line)) {
        vector<string> tokens = tokenize(line, ",");
        assert(tokens.size() == 5);

        string id       = tokens[0];
        string username = tokens[1];
        string email    = tokens[2];
        string age      = tokens[3];
        string location = tokens[4];

        bool ok_id       = !id.empty();
        for(auto& x: id) ok_id &= bool(isalnum(x));

        bool ok_username = !username.empty();
        for(auto& x: username) ok_username &= bool(isalnum(x));

        regex email_pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
        bool ok_email = !email.empty() && regex_match(email, email_pattern);

        bool ok_age = true;
        if(!age.empty())
            for(auto& x: age)
                ok_age &= isdigit(x);

        bool ok_location = true;
        if(!location.empty())
            for(auto& x: location)
                ok_location &= (x == ' ' || isalpha(x));

        bool ok = ok_id && ok_username && ok_email && ok_age && ok_location;
        if(!ok) bads.emplace_back(username);
    }

    string ans = "";
    for(auto& x: bads)
        if(!x.empty())
            ans += x.front();
    cout << ans << "\n";
}
