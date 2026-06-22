#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, A, B; cin >> n >> A >> B;
    deque<char> q;
    string S; cin >> S;
    for(int i = 0; i < n; i++) {
        q.emplace_back(S[i]);
    }
    for(int i = 0; i < A; i++) {
        q.pop_front();
    }
    for(int i = 0; i < B; i++) {
        q.pop_back();
    }
    for(auto& x: q) cout << x;
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
