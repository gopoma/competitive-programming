#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, string>>> V(m+1);
    for(int i = 0; i < n; i++) {
        string surname;
        cin >> surname;

        int region, points;
        cin >> region >> points;

        V[region].emplace_back(make_pair(points, surname));
    }

    for(auto& v: V)
        sort(v.rbegin(), v.rend());

    for(int i = 1; i <= m; i++) {
        if(int(V[i].size()) > 2 && V[i][1].first == V[i][2].first)
            cout << "?\n";
        else
            cout << V[i][0].second << " " << V[i][1].second << "\n";
    }

    return 0;
}
