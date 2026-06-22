#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    const int CANTIDAD_RONDAS = 18;
    int pares[CANTIDAD_RONDAS];
    for(int i = 0; i < CANTIDAD_RONDAS; i++) {
      cin >> pares[i];
    }



    int N;
    cin >> N;
    vector<pair<int, string>> count(N);
    for(int i = 0; i < N; i++) {
        string id;
        cin >> id;

        int score = 0;
        for(int j = 0; j < CANTIDAD_RONDAS; j++) {
            int golpes;
            cin >> golpes;

            score += golpes - pares[j];
        }

        count[i] = { score, id };
    }

    sort(count.begin(), count.end());

    for(auto& p: count) {
        cout << p.second << " ";
        if(p.first > 0) {
            cout << "+" << p.first;
        } else if(p.first == 0) {
            cout << "E";
        } else {
            cout << p.first;
        }
        cout << "\n";
    }

    return 0;
}
