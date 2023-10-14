#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;

    int count = 0;
    for(int b = 0; b < (1<<n); b++) {
        vector<int> subset;
        for(int i = 0; i < n; i++) {
            if(b&(1<<i)) subset.push_back(i);
        }

        cout << count << ": ";
        for(int i = 0; i < int(subset.size()); i++) {
            cout << subset[i] << " \n"[i == int(subset.size()) - 1];
        }
        if(count == 0) cout << "\n";

        count++;
    }

    return 0;
}
