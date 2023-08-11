#include <bits/stdc++.h>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

typedef long long ll;
typedef long double ld;

bool isInteger(ld num) {
    return num == ceil(num);
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    ll N;
    cin >> N;
    unordered_map<ll, ll> points;
    vector<ll> radius(N);

    for(ll i = 0; i < N; i++) {
        ll R, P;
        cin >> R >> P;
        radius[i] = R;
        points[R] = P;
    }
    points[-1] = 0;
    sort(radius.begin(), radius.end());



    ll result = 0, M; cin >> M;
    for(ll i = 0; i < M; i++) {
        ll X, Y; cin >> X >> Y;
        ld distance = sqrt(X*X + Y*Y);

        auto k = upper_bound(radius.begin(), radius.end(), distance);
        ll inc = points[*k];
        result += inc;
    }
    cout << result << "\n";

    return 0;
}
