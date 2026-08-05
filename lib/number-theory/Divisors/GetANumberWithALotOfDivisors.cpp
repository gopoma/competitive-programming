#include <bits/stdc++.h>
using namespace std;

unsigned long long n, res;
int p, primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 51, 53, 59, 61, 67, 71};

unsigned long long mul(unsigned long long a, unsigned long long b){
    unsigned long long res = 0;

    while (b){
        if (b & 1LL) res = (res + a);
        if (res >= n) return 0;
        a = (a << 1LL);
        b >>= 1LL;
    }

    return res;
}

unsigned long long val_response = 67;
void backtrack(int i, int lim, unsigned long long val, unsigned long long r){
    if (r > res) {
        res = r;
        val_response = val;
    }
    if (i == p) return;

    int d;
    unsigned long long x = val;

    for (d = 1; d <= lim; d++){
        x = mul(x, primes[i]);
        if (x == 0) return;
        backtrack(i + 1, d, x, r * (d + 1));
    }
}

int main(){
    /* Tested for n <= 10^18 */

    p = sizeof(primes) / sizeof(int);

    cin >> n;
    res = 0;
    backtrack(0, 100, 1, 1);
    printf("Maximum number of divisors of any number less than %llu = %llu\n", n, res);
    printf("Value %llu = %llu\n", n, val_response);

    return 0;
}
