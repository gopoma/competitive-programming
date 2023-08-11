#include <iostream>
#include <string>
#include <map>

using namespace std;

using ll = long long;

string solve(string s) {
    if(s.size() == 0) {
        return "";
    }

    map<char, ll> tmp;

    char prev = s[0];
    tmp[prev] = 1;

    string result = "";

    for(int i = 1; i < s.size(); i++) {
        const char current = s[i];

        if(current == prev) {
            tmp[current]++; 
        } else {
            result += prev + to_string(tmp[prev]);
            tmp[prev] = 0;
            
            tmp[current] = 1;
            prev = current;
        }
    }

    result += prev + to_string(tmp[prev]);

    return (result.size() < s.size())? result : s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << solve("aabcccccaaa") << endl;
    cout << solve("x")           << endl;

    return 0;
}
