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
    auto give = [&](db T, db D, db H) -> void {
        //? T 30.0 D 15.0 H 34.0
        cout << "T " << T << " D " << D << " H " << H << "\n";
    };
    map<char, int> idx;
    idx['T'] = 1;
    idx['D'] = 2;
    idx['H'] = 3;
    char have, have2;
    db val, val2;
    while(true) {
        cin >> have;
        if(have == 'E') return;
        else {
            cin >> val >> have2 >> val2;
            dbg(have, val, have2, val2);
            if(idx[have] > idx[have2]) {
                swap(have, have2);
                swap(val, val2);
            }
            dbg(have, val, have2, val2);
            if(have == 'T' && have2 == 'D') {
                db temperature = val;
                db dewpoint = val2;
                //? humidex = temperature + h
                //? h = (0.5555) ∗ (e − 10.0)
                //? e = 6.11 ∗ exp[5417.7530 ∗ ((1/273.16) − (1/(dewpoint + 273.16)))]
                db e = db(6.11) * expl(db(5417.7530) * ((db(1)/db(273.16)) - (db(1)/(dewpoint + db(273.16)))));
                db h = db(0.5555) * db(e - db(10.0));
                db humidex = temperature + h;
                give(temperature, dewpoint, humidex);
            } else if(have == 'T' && have2 == 'H') {
                db temperature = val;
                db humidex = val2;
                //? humidex = temperature + h
                //? h = (0.5555) ∗ (e − 10.0)
                //? e = 6.11 ∗ exp[5417.7530 ∗ ((1/273.16) − (1/(dewpoint + 273.16)))]
                //? e = 6.11 ∗ exp[X]
                //? X = 5417.7530 ∗ ((1/273.16) − (1/(dewpoint + 273.16)))
                //? X = 5417.7530 ∗ Y
                //? Y = (1/273.16) − (1/(dewpoint + 273.16))
                //? Y = (1/273.16) − Z
                //? Z = (1/273.16) - Y
                //? Z = (1/(dewpoint + 273.16))
                //? Z = (1/W)
                //? W = 1/Z
                //? W = dewpoint + 273.16
                db h = humidex - temperature;
                db e = (h / db(0.5555)) + db(10.0);
                db X = logl(e / db(6.11)) / logl(expl(db(1)));
                db Y = X / db(5417.7530);
                db Z = (db(1)/db(273.16)) - Y;
                db W = db(1)/Z;
                db dewpoint = W - db(273.16);
                give(temperature, dewpoint, humidex);
            } else {
                //? humidex = temperature + h
                //? h = (0.5555) ∗ (e − 10.0)
                //? e = 6.11 ∗ exp[5417.7530 ∗ ((1/273.16) − (1/(dewpoint + 273.16)))]
                assert(have == 'D' && have2 == 'H');
                db dewpoint = val;
                db humidex = val2;
                db e = db(6.11) * expl(db(5417.7530) * ((db(1)/db(273.16)) - (db(1)/(dewpoint + db(273.16)))));
                db h = db(0.5555) * db(e - db(10.0));
                db temperature = humidex - h;
                give(temperature, dewpoint, humidex);
            }
        }
        RAYA;
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cout << fixed << setprecision(1);
    cerr << fixed << setprecision(1);

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
