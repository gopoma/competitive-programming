#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

pair<ll, ll> getNums(string s) {
    ll separatorPosition = -1;
    for(ll i = 0; i < s.size(); i++) {
        if(s[i] == '-') {
            separatorPosition = i;
            break;
        }
    }

    // X-Y
    const ll firstNum  = stoi(s.substr(0, separatorPosition));
    const ll secondNum = stoi(s.substr(separatorPosition + 1, s.size() - separatorPosition - 1));

    return { firstNum, secondNum };
}

void solve() {
    ll n;
    cin >> n;

    vector<string> scores;
    for(ll i = 0; i < n; i++) {
        string s;
        cin >> s;

        scores.push_back(s);
    }

    string firstScoreStr = scores[0];

    if(firstScoreStr == "11-11") {
        cout << "error 1\n";
        return;
    }

    pair<ll, ll> prevScore = getNums(firstScoreStr);
    ll prevScoreSum = prevScore.F + prevScore.S;
    if(((prevScoreSum - 1) % 4) == 0 || ((prevScoreSum - 2) % 4) == 0) {
        swap(prevScore.F, prevScore.S);
    }

    for(ll i = 1; i < n; i++) {
        pair<ll, ll> currentScore = getNums(scores[i]);



        ll currentSum = currentScore.F + currentScore.S;
        if(((currentSum - 1) % 4) == 0 || ((currentSum - 2) % 4) == 0) {
            swap(currentScore.F, currentScore.S);
        }

        if(prevScore.F > currentScore.F || prevScore.S > currentScore.S || (max(prevScore.F, prevScore.S) == 11 && prevScore != currentScore)) {
            cout << "error " << (i + 1) << "\n";
            return;
        }

        prevScore.F = currentScore.F;
        prevScore.S = currentScore.S;
    }

    cout << "ok\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
