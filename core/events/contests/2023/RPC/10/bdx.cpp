#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

string eval(vector<int> &A, vector<int> &B)
{
    int y1 = A[0], x1 = A[1], y2 = B[0], x2 = B[1];
    if (x1 == x2)
        return "##" + to_string(x1);
    if (y1 == y2)
        return to_string(y1) + "##";
    int a = y2 - y1, b = x2 - x1;

    int g = __gcd(a, b);
    a /= g, b /= g;
    if (a < 0)
        a = -a, b = -b;

    long double c = y1 - 1.0 * a / b * x1;
    return to_string(a) + "#" + to_string(b) + "#" + to_string(c);
}

bool ok(vector<vector<int>> &A)
{
    if (A.size() == 0)
        return true;
    if (A.size() == 1)
        return true;
    unordered_map<string, int> freq;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = i + 1; j < A.size(); j++)
        {
            freq[eval(A[i], A[j])] |= (1 << i) | (1 << j);
        }
    }

    int rem = (1 << A.size()) - 1;
    DBG(rem);
    int res = 0;
    while (rem)
    {
        string line = "";
        int cnt = 0;
        for (auto [l, c] : freq)
        {
            if (__builtin_popcount(c) > cnt)
            {
                cnt = __builtin_popcount(c);
                line = l;
            }
        }
        int mask = freq[line];
        for (auto &[l, c] : freq)
        {
            c &= ~mask;
        }
        rem &= ~mask;
        res++;
        if(res > 3) {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> A(n);

    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        A[i] = {x, y};
    }

    bool xd = ok(A);
    cout << (xd?"possible":"impossible") << "\n";
}
