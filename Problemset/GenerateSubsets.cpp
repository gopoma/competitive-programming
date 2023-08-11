#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void generateSubsets(vector<ll> ss, vector<ll> tmp, ll k, vector<vector<ll>> subsets, ll* counter, ll target) {
    if(k == ss.size()) {
        ll sum = 0;
        for(auto ee: tmp) {
            sum += ee;
        }

        if(sum == target) {
            (*counter)++;
            for(auto ee: tmp) {
                cout << ee << " ";
            }
            cout << "\n";
        }
    } else {
        generateSubsets(ss, tmp, k + 1, subsets, counter, target);
        tmp.push_back(ss[k]);
        generateSubsets(ss, tmp, k + 1, subsets, counter, target);
        tmp.pop_back();
    }
}

void solve() {
    vector<ll> ss = {1, 2, 3, 4, 5};
    vector<ll> tmp;
    vector<vector<ll>> subsets;

    ll counter = 0, target = 10;
    generateSubsets(ss, tmp, 0LL, subsets, &counter, target);
    assert(counter == 3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
