// template: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/contest/TemplateLong.cpp

#pragma GCC optimize(3,"Ofast","inline")

#include <bits/stdc++.h>

using namespace std;

// building blocks
using ll = long long;
using ull = unsigned long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!
using u128 = __uint128_t; // for Number Theory related
using i128 = __int128;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>; // minima

inline namespace FileIO {
	void setIn(str s)  { freopen(s.c_str(),"r",stdin); }
	void setOut(str s) { freopen(s.c_str(),"w",stdout); }
	void setIO(str s = "") {
		cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
		// cin.exceptions(cin.failbit);
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (int(s.size())) setIn(s+".in"), setOut(s+".out"); // for old USACO
	}
}

// for debugging!
#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

// https://codeforces.com/blog/entry/75044
__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void xdprint(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) xdprint(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }

// https://www.codeconvert.ai/assembly-to-c++-converter
using tint = long long;
const bool ddd = false;
tint work(tint A, tint B, tint C) {
    //!
    if(B <= C) return B;
    //!

    tint v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18;

    v0 = A;
    v1 = B;
    v2 = C;

    v3 = 1; // const/32 v3,1
    v4 = v3 - v3; // sub-int v4,v3,v3
    v5 = v4 - v3; // sub-int v5,v4,v3
    v6 = v3; // move v6,v3
    v7 = v4; // move v7,v4
    v7 = v7 - v1; // sub-int v7,v7,v1
    v8 = v0; // move v8,v0
    v9 = v0; // move v9,v0
    v9 = v0 + v1; // add-int v9,v0,v1
    v10 = v4; // move v10,v4
    v11 = v4; // move v11,v4
    v12 = v3; // move v12,v3

    // l0
    while (true) {
        v11 = v11 + v1; // add-int v11,v11,v1
        v10 = v10 + v0; // add-int v10,v10,v0
        v13 = v10; // move v13,v10
        v14 = v4; // move v14,v4
        v15 = v4; // move v15,v4

        // l1
        while (true) {
            v16 = v13 + v13; // add-int v16,v13,v13
            // if(ddd) DBG3(1, v16, v1);
            if (v16 <= v1) {
                break;
            }
            v13 = v13 - v1; // sub-int v13,v13,v1
            v14 = v14 + v3; // add-int v14,v14,v3
            v15 = v15 + v1; // add-int v15,v15,v1
        }

        // l2
        while(true) {
            // if(ddd)DBG3(2, v13, v4);
            if(v13 > v4) {
                break;
            }
            v13 = v4 - v13; // sub-int v13,v4,v13
            break;
        }

        // l3
        while(true) {
            v17 = v4; // move v17,v4
            v18 = v3; // move v18,v3

            break;
        }

        // l4
        while (true) {
            v17 = v17 + v13; // add-int v17,v17,v13
            v18 = v18 + v3; // add-int v18,v18,v3
            // if(ddd)DBG3(3, v18, v6);
            if (v18 <= v6) {
                continue;
            }
            v18 = v3;

            break;
        }

        // l5
        // if(ddd) DBG4(3.5, v17, v4, v9);
        while (true) {
            v17 = v17 - v9; // sub-int v17,v17,v9
            v18 = v18 + v3; // add-int v18,v18,v3
            // if(ddd) DBG4(4, v18, v12, v9);
            if (v18 <= v12) {
                continue;
            }
            // if(ddd) DBG4(4, v17, v4, v9);
            if (v17 >= v4) {
                break;
            }
            v5 = v14;
            v6 = v12;
            v7 = v15;
            v8 = v10;
            v9 = v13;

            break;
        }

        // l6
        v12 = v12 + v3;
        // if(ddd) DBG3(5, v12, v2);
        if (v12 <= v2) {
            continue;
        }

        break;
    }

    return v6;
}

signed main() {
    // read read read
	setIO();

    long long t = 1LL;
    cin >> t;
    // tint t = read();

    while(t--) {
        tint A, B, C;
        cin >> A >> B >> C;
        // A = 100;
        // A = read();
        // B = read();
        // C = read();
        tint ans = work(A, B, C);
        // DBG(ans);
        cout << ans << "\n";
        // xdprint(ans);
        // printf("\n");

        // for(long long A = 13; A <= 13; A++) {
        //     for(long long B = 29; B <= 29; B++) {
        //         for(long long C = 1; C <= 100; C++) {
        //             long long ans = work(A, B, C);
        //             DBG4(A, B, C, ans);
        //             // DBG4(A + 1, B, C, ans);
        //             // DBG4(A + 2, B, C, ans);
        //             // DBG4(A + 3, B, C, ans);
        //             // RAYA;
        //         }
        //     }
        // }
    }

    // should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/

//! ERASE DBGs xd or TLE
