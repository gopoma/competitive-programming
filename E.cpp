#include <bits/stdc++.h>
using namespace std;

bool isLuckyNumber(int x) {
    bool ok = true;
    for(auto& c: to_string(x)) {
        ok &= (c == '4' || c == '7');
    }
    return ok;
}

bool hasLuckyNumber(vector<int>& a) {
    return any_of(a.begin(), a.end(), [](const int& x) {
        return isLuckyNumber(x);
    });
}

signed main() {
    vector<int> nums1 = {2, 9, 12, 13, 16, 47};
    vector<int> nums2 = {1, 3, 6, 10, 15};

    bool res1 = hasLuckyNumber(nums1);
    bool res2 = hasLuckyNumber(nums2);

    cout << "res1: " << res1 << "\n";
    cout << "res2: " << res2 << "\n";
}
