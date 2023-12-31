#include <bits/stdc++.h>

using namespace std;

signed main() {
    double m, n, a;
    cin >> m >> n >> a;

    double mm = a * ceil(m / a);
    double nn = a * ceil(n / a);

    double ans = (mm / a) * (nn / a);
    cout << (long long)(ans) << "\n";

    return 0;
}
