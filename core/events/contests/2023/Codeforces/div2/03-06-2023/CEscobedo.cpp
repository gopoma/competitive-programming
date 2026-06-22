#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool komp(const ll& a, const ll& b) {
    return a > b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, q; cin >> n >> q;
    set<ll> tmp;

    while(q--) {
        char a;
        cin >> a;
        if(a=='-'){
            ll num;
            cin>>num;
            tmp.insert(num);
        }
        else if(a=='+') {
            ll num;
            cin>>num;
            tmp.erase(num);
        }
        else {
            ll n1,n2;
            cin>>n1>>n2;
            ll aux = min(n1, n2);
            n2 = max(n1, n2);
            n1 = aux;

            if(tmp.empty()) {
                cout << "possible\n";
            } else if(tmp.size() == 1) {
                if(tmp.count(n1) == 0 && tmp.count(n2) == 0) {
                    cout << "possible\n";
                } else {
                    cout << "impossible\n";
                }
            } else {
                if(tmp.count(n1) != 0 || tmp.count(n2) != 0) {
                    cout << "impossible\n";
                } else {
                    ll minSetValue = *(tmp.begin()); // min
                    ll maxSetValue = *(tmp.rbegin()); // max

                    ll minLimit, maxLimit;
                    //cout << minLimit << " " << maxLimit << "\n";
                    //cout << minSetValue << " " << maxSetValue << "\n";

                    if(n1 < minSetValue) {
                        minLimit = *lower_bound(tmp.begin(), tmp.end(), n1);
                        maxLimit = maxSetValue;
                    } else if(n1 > maxSetValue) {
                        minLimit = minSetValue;
                    maxLimit = *upper_bound(tmp.rbegin(), tmp.rend(), n1, komp);
                    } else {
                        minLimit = *upper_bound(tmp.rbegin(), tmp.rend(), n1, komp);
                        maxLimit = *lower_bound(tmp.begin(), tmp.end(), n1);
                    }

                    if(
                        ((minLimit < n1 && n1 < maxLimit) && (n2 <= minLimit || maxLimit <= n2)) ||
                        ((n1 <= minLimit || maxLimit <= n1) && (minLimit < n2 && n2 < maxLimit))
                    ) {
                        cout << "impossible\n";
                    } else {
                        cout << "possible\n";
                    }
                }
            }
        }
    }

    return 0;
}
