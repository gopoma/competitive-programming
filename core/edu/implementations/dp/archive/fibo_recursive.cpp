#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 4e5 + 4;
bool is_computed[MAXN]{false};
long long F[MAXN]{-1LL};

long long fibo(int  i) {
    if(i < 2LL) {
        return i;
    }
    if(is_computed[i]) {
        assert(F[i] != -1LL);
        return F[i];
    }

    F[i] = (long long)fibo(i - 1) + (long long)fibo(i - 2);
    is_computed[i] = true;
    // printf("\nComputed\n");
    return F[i];
}

signed main() {
    vector<long long> fibos = {0LL, 1LL, 1LL, 2LL, 3LL, 5LL, 8LL, 13LL, 21LL, 34LL, 55LL};
    for(int i = 0; i < (int)fibos.size(); i++) {
        cout << "i: " << i << "\tF[i]: " << fibo(i) << "\n";
        assert(fibo(i) == fibos[i]);
    }
    printf("OK\n");

    return 0;
}
