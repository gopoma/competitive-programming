#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

bool isInteger(ld num) {
    return num == ceil(num);
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    vector<int> v = {10, 20, 30, 40, 50};
    double x = 50.6;
    auto k = upper_bound(v.begin(), v.end(), x);
    cout << *k << "\n";

    return 0;
}
