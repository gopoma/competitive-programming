#include <bits/stdc++.h>

using namespace std;

signed main() {
    int T;
    scanf("%d", &T);

    for(int _ = 0; _ < T; _++) {
        int L, V1, V2;
        scanf("%d %d %d", &L, &V1, &V2);

        assert(V1 < V2);

        int t1 = ceil(L / (long double)V1);
        int t2 = ceil(L / (long double)V2);

        if(t1 == t2) printf("-1\n");
        else {
            int ans = t1 - t2 - 1;
            printf("%d\n", ans);
        }
    }

    return 0;
}
