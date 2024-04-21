#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;

    vector<string> A(n);
    for(auto& a: A)
        cin >> a;

    sort(A.begin(), A.end(), [](const string& a, const string& b){
        if(a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });

    for(auto& a: A)
        cout << a << "\n";

    return 0;
}
