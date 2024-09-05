#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "helpers/debug.h"

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define RAYA
#endif

template<class T> using V = vector<T>;
#define all(x) begin(x), end(x)

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

using ll = long long;
using db = long double;

void solve() {
    vector<pair<int, int>> directions{
        make_pair(+0, -1),
        make_pair(+1, -1),
        make_pair(+1, +0),
        make_pair(+0, +1),
        make_pair(-1, +1),
        make_pair(-1, +0),
    };
    map<pair<int, int>, bool> vis;
    vector<pair<int, int>> ans(100005);

    int timer = 1;
    vis[make_pair(0, 0)] = true;
    vis[make_pair(0, 1)] = true;
    ans[timer++] = make_pair(0, 0);
    ans[timer++] = make_pair(0, 1);

    int current_x = 0;
    int current_y = 1;
    for(int _ = 0; _ < 100002; _++) {
        int idx = 0;
        for(idx; idx < 6; idx++) {
            auto [dx, dy] = directions[idx];
            if(vis[make_pair(current_x + dx, current_y + dy)]) {
                break;
            }
        }
        idx--; if(idx < 0) idx += 6;
        while(vis[make_pair(current_x + directions[idx].first, current_y + directions[idx].second)]) {
            idx--; if(idx < 0) idx += 6;
        }

        auto [dx, dy] = directions[idx];
        current_x += dx;
        current_y += dy;
        vis[make_pair(current_x, current_y)] = true;
        ans[timer++] = make_pair(current_x, current_y);
    }

    //? for(int x = 1; x <= 20; x++) dbg(x, ans[x]);

    vector<pair<int, int>> response;
    ll N;
    while(cin >> N) {
        auto [xx, yy] = ans[N];
        cout << xx << " " << yy << "\n";
    }
//?        response.emplace_back(xx, yy);
//?    }
//?    {
//?        const int M = int(response.size());
//?        for(int i = 0; i < M; i++) {
//?            auto [xx, yy] = response[i];
//?            cout << xx << " " << yy << "\n";
//?        }
//?    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
