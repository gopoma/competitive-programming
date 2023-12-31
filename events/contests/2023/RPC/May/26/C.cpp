#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n;
    cin >> n;

    string s;
    cin >> s;

    ll amountLessons = 0;
    ll currentCoffeeCups = 0;

    for(ll i = 0; i < n; i++) {
        const bool hasCoffeMachine = s[i] == '1';

        if(hasCoffeMachine) {
            currentCoffeeCups = 2;
            amountLessons++;
        } else {
            if(currentCoffeeCups > 0) {
                amountLessons++;
                currentCoffeeCups--;
            }
        }
    }

    cout << amountLessons << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
