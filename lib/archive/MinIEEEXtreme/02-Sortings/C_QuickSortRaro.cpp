#include <bits/stdc++.h>

using namespace std;

int comparisons;

void partition(int pivot, vector<int>& a, vector<int>& L, vector<int>& R) {
    for(int i = 0; i < int(a.size()); i++) {
        if(i == pivot) continue;

        comparisons += 1;

        if(a[i] <= a[pivot])
            L.emplace_back(a[i]);
        else
            R.emplace_back(a[i]);
    }
}

vector<int> Quicksort(vector<int>& a) {
    if(int(a.size()) <= 1) {
        return a;
    }

    int pivot = int(a.size()) / 2;

    vector<int> L, R;
    partition(pivot, a, L, R);

    L = Quicksort(L);
    R = Quicksort(R);

    L.emplace_back(a[pivot]);
    L.insert(L.end(), R.begin(), R.end());

    return L;
}

void brute() {
    // <>
    // 0 1 3 6 10 15 21 28 36 45 -> n*(n+1)/2
    const int N = 3;
    vector<int> V(N);
    for(int i = 1; i <= N; i++) {
        V[i - 1] = i;
    }



    int max_comparisons = 0;
    do {
        comparisons = 0;

        vector<int> res = Quicksort(V);

        max_comparisons = max(max_comparisons, comparisons);
    } while(next_permutation(V.begin(), V.end()));



    for(int i = 1; i <= N; i++) {
        V[i - 1] = i;
    }

    do {
        comparisons = 0;

        vector<int> res = Quicksort(V);

        if(comparisons == max_comparisons) {
            for(auto& e: V)
                cout << e << " ";
            cout << "\n";

            cout << "comparisons: " << comparisons << "\n\n";
        }
    } while(next_permutation(V.begin(), V.end()));
}

void solve() {
    // <>

    int n;
    cin >> n;

    // 1: 1
    // 2: 1 2
    // 3: 2 1 3
    // 4: 2 1 4 3
    // 5: 3 2 1 5 4
    // 6: 3 2 1 6 5 4

    vector<int> ans;

    for(int i = ceil(n/2.0); i >= 1; i--)
        ans.emplace_back(i);

    for(int i = n; i > ceil(n/2.0); i--)
        ans.emplace_back(i);

    comparisons = 0;
    Quicksort(ans);
    // cout << comparisons << " " << (((n-1)*(n))/2) << "\n";
    assert(comparisons == ((n-1)*(n))/2);

    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute();
    solve();

    return 0;
}
