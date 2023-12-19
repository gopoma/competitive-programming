#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <thread>
#include <sstream>
#include <chrono>
#include <ctime>
#include <mutex>

using namespace std;

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define DBG(x)        0
    #define DBGY(x)       0
    #define DBG2(x,y)     0
    #define DBG3(x,y,z)   0
    #define DBG4(x,y,z,w) 0
    #define RAYA          0
#endif

inline namespace FileIO {
	void setIn(string s)  { freopen(s.c_str(),"r",stdin); }
	void setOut(string s) { freopen(s.c_str(),"w",stdout); }
	void setIO(string s = "") {
		cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
		// cin.exceptions(cin.failbit);
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (int(s.size())) setIn(s+".in"), setOut(s+".out"); // for old USACO
	}
}

vector<string> tokenize(string line, string separator) {
    vector<string> tokens;
    while(true) {
        string token = line.substr(0, line.find(separator));
        tokens.emplace_back(token);

        if(line.find(separator) == string::npos) {
            break;
        }
        line = line.substr(line.find(separator) + 1, int(line.size()) - line.find(separator) + 1);
    }
    return tokens;
};

clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

signed main() {
    startTime = clock();

    cin.tie(0)->sync_with_stdio(0);
    setIn("ratings_s.csv");
    setOut("E2");

    string line;
    unordered_map<int, unordered_map<int, long double>> bd;
    vector<int> users;
    while(cin >> line) {
        vector<string> tokens = tokenize(line, ",");
        int idUser = stoi(tokens[0]);
        int idMovie = stoi(tokens[1]);
        long double rating = stold(tokens[2]);

        bd[idUser][idMovie] = rating;
        users.emplace_back(idUser);
    }

    // sort and remove duplicates
    sort(users.begin(), users.end());
    users.erase(unique(users.begin(), users.end()), end(users));
    assert(int(bd.size()) == int(users.size()));

    map<int, map<int, long double>> Manhattan;
    map<int, map<int, long double>> Euclidean;

    const int n = int(users.size());
//    mutex workerLock;
//    auto work = [&](int u) {
//        for(int v = u + 1; v < n; v++) {
//            //? Manhattan distance between u and v
//            long double mhdist = 0;
//            //? Euclidean distance between u and v
//            long double edist = 0;
//
//            unordered_set<int> vis;
//            for(auto& [idMovie, _]: bd[u]) {
//                vis.emplace(idMovie);
//
//                workerLock.lock();
//                long double delta = bd[u][idMovie] - bd[v][idMovie];
//                workerLock.unlock();
//
//                mhdist += abs(delta);
//                edist += delta * delta;
//            }
//
//            for(auto& [idMovie, _]: bd[v]) {
//                if(vis.count(idMovie)) continue;
//
//                workerLock.lock();
//                long double delta = bd[v][idMovie] - bd[u][idMovie];
//                workerLock.unlock();
//
//                mhdist += abs(delta);
//                edist += delta * delta;
//            }
//
//            workerLock.lock();
//            Manhattan[u][v] = mhdist;
//            Manhattan[v][u] = mhdist;
//            workerLock.unlock();
//
//            edist = sqrt(edist);
//            workerLock.lock();
//            Euclidean[u][v] = edist;
//            Euclidean[v][u] = edist;
//            workerLock.unlock();
//        }
//    };

    // vector<thread> Workers;
    for(int u = 0; u < n; u++) {
        dbg(u);
        for(int v = u + 1; v < n; v++) {
            //? Manhattan distance between u and v
            long double mhdist = 0;
            //? Euclidean distance between u and v
            long double edist = 0;

            unordered_set<int> vis;
            for(auto& [idMovie, _]: bd[u]) {
                vis.emplace(idMovie);

                // workerLock.lock();
                long double delta = bd[u][idMovie] - bd[v][idMovie];
                // workerLock.unlock();

                mhdist += abs(delta);
                edist += delta * delta;
            }

            for(auto& [idMovie, _]: bd[v]) {
                if(vis.count(idMovie)) continue;

                // workerLock.lock();
                long double delta = bd[v][idMovie] - bd[u][idMovie];
                // workerLock.unlock();

                mhdist += abs(delta);
                edist += delta * delta;
            }

            // workerLock.lock();
            Manhattan[u][v] = mhdist;
            Manhattan[v][u] = mhdist;
            // workerLock.unlock();

            edist = sqrt(edist);
            // workerLock.lock();
            Euclidean[u][v] = edist;
            Euclidean[v][u] = edist;
            // workerLock.unlock();
        }
        // Workers.emplace_back(work, u);
    }

    // for(auto& w: Workers) {
    //     w.join();
    // }

    dbg(int(users.size()));
    dbg(int(Manhattan.size()));
    dbg(int(Euclidean.size()));

    map<int, vector<pair<int, long double>>> recomendableM;
    map<int, vector<pair<int, long double>>> recomendableE;
    const int m = 5;
    for(int u = 0; u < n; u++) {
        vector<pair<long double, int>> mh;
        vector<pair<long double, int>> e;
        for(auto& [v, mhdist]: Manhattan[u]) {
            mh.emplace_back(make_pair(mhdist, v));
        }

        for(auto& [v, edist]: Euclidean[u]) {
            e.emplace_back(make_pair(edist, v));
        }

        sort(mh.rbegin(), mh.rend());
        sort(e.rbegin(), e.rend());

        assert(int(mh.size()) >= m);
        assert(int(e.size()) >= m);
        for(int k = 0; k < m; k++) {
            recomendableM[u].emplace_back(make_pair(mh[k].second, mh[k].first));
            recomendableE[u].emplace_back(make_pair(e[k].second, e[k].first));
        }
    }

    ofstream ManhattanFile, EuclideanFile;
    ManhattanFile.open("ManhattanRecomendable.csv");
    for(auto& [u, results]: recomendableM) {
        ManhattanFile << u << ",";
        for(auto& [v, val]: results) {
            ManhattanFile << v << "," << val << ",";
        }
        ManhattanFile << "\n";
    }
    ManhattanFile.close();

    EuclideanFile.open("EuclideanRecomendable.csv");
    for(auto& [u, results]: recomendableE) {
        EuclideanFile << u << ",";
        for(auto& [v, val]: results) {
            EuclideanFile << v << "," << val << ",";
        }
        EuclideanFile << "\n";
    }
    EuclideanFile.close();

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << getCurrentTime() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
