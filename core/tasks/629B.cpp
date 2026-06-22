#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<char> a(n);
    vector<int> l(n);
    vector<int> r(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> l[i] >> r[i];
    }

    int res = 0;
    for(int d = 1; d <= 366; d++) {
        vector<int> cnt(2);
        for(int i = 0; i < n; i++) {
            if(l[i] <= d && d <= r[i]) {
                if(a[i] == 'M') cnt[0]++;
                else cnt[1]++;
            }
        }
        res = max(res, 2 * min(cnt[0], cnt[1]));
    }
    cout << res << "\n";
    return 0;
}
