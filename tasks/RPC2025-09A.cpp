#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0

struct minstack {
	stack<pair<int, int>> st;
	int getmin() {return st.top().second;}
	bool empty() {return st.empty();}
	int size() {return st.size();}
	void push(int x) {
		int mn = x;
		if (!empty()) mn = min(mn, getmin());
		st.push({x, mn});
	}
	void pop() {st.pop();}
	int top() {return st.top().first;}
	void swap(minstack &x) {st.swap(x.st);}
};

struct mindeque {
	minstack l, r, t;
	void rebalance() {
		bool f = false;
		if (r.empty()) {f = true; l.swap(r);}
		int sz = r.size() / 2;
		while (sz--) {t.push(r.top()); r.pop();}
		while (!r.empty()) {l.push(r.top()); r.pop();}
		while (!t.empty()) {r.push(t.top()); t.pop();}
		if (f) l.swap(r);
	}
	int getmin() {
		if (l.empty()) return r.getmin();
		if (r.empty()) return l.getmin();
		return min(l.getmin(), r.getmin());
	}
	bool empty() {return l.empty() && r.empty();}
	int size() {return l.size() + r.size();}
	void push_front(int x) {l.push(x);}
	void push_back(int x) {r.push(x);}
	void pop_front() {if (l.empty()) rebalance(); l.pop();}
	void pop_back() {if (r.empty()) rebalance(); r.pop();}
	int front() {if (l.empty()) rebalance(); return l.top();}
	int back() {if (r.empty()) rebalance(); return r.top();}
	void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
};

void solve() {
    int n, m; cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> a[i][j];

    int r, s; cin >> r >> s;

    vector<vector<int>> b;
    mindeque st;

    // work for rows
    for(int row = 0; row < n; row++) {
        while(!st.empty()) st.pop_back();

        vector<int> cur;
        for(int col = 0; col < m; col++) {
            st.push_back(-a[row][col]);
            while(!st.empty() && st.size() > s) st.pop_front();
            if(st.size() == s)
                cur.emplace_back(-st.getmin());
        }
        b.emplace_back(cur);
    }

    vector<vector<int>> re(n - (r - 1), vector<int>(m - (s - 1)));
    for(int col = 0; col < int(b[0].size()); col++) {
        while(!st.empty()) st.pop_back();

        vector<int> cur;
        for(int row = 0; row < int(b.size()); row++) {
            st.push_back(-b[row][col]);
            while(!st.empty() && st.size() > r) st.pop_front();
            if(st.size() == r)
                cur.emplace_back(-st.getmin());
        }

        for(int i = 0; i < int(cur.size()); i++) {
            re[i][col] = cur[i];
        }
    }

    const int N = int(re.size());
    const int M = int(re[0].size());

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cout << re[i][j];
            if(j == M - 1) continue;
            else cout << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
