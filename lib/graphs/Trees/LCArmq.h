/**
 * Description: Euler Tour LCA. Compress takes a subset $S$ of nodes
 	* and computes the minimal subtree that contains all the nodes
	* pairwise LCAs and compressing edges. Returns a list of
	* \texttt{(par, orig\_index)} representing a tree rooted at 0.
	* The root points to itself.
 * Time: O(N\log N) build, O(1) LCA, O(|S|\log |S|) compress
 * Source: USACO, Simon Lindholm (KACTL)
 * Verification: USACO Debug the Bugs
 	* https://codeforces.com/contest/1320/problem/E
 */

//? #include "../../data-structures/Static Range Queries (9.1)/RMQ (9.1).h"

/**
 * Description: 1D range minimum query. If TL is an issue, use
	* arrays instead of vectors and store values instead of indices.
 * Source: KACTL
 * Verification:
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N\log N)
 * Time: O(1)
 */

tcT> struct RMQ { // floor(log_2(x))
	int level(int x) { return 31-__builtin_clz(x); }
	V<T> v; V<vi> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); }
	void init(const V<T>& _v) {
		v = _v; jmp = {vi(sz(v))};
		iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};

struct LCA {
	int N; V<vi> adj;
	vi depth, pos, par, rev; // rev is for compress
	vpi tmp; RMQ<pi> r;
	void init(int _N) { N = _N; adj.rsz(N);
		depth = pos = par = rev = vi(N); }
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfs(int x) {
		pos[x] = sz(tmp); tmp.eb(depth[x],x);
		each(y,adj[x]) if (y != par[x]) {
			depth[y] = depth[par[y]=x]+1, dfs(y);
			tmp.eb(depth[x],x); }
	}
	void gen(int R = 0) { par[R] = R; dfs(R); r.init(tmp); }
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vpi compress(vi S) {
		auto cmp = [&](int a, int b) { return pos[a] < pos[b]; };
		sort(all(S),cmp); R0F(i,sz(S)-1) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); S.erase(unique(all(S)),end(S));
		vpi ret{{0,S[0]}}; F0R(i,sz(S)) rev[S[i]] = i;
		FOR(i,1,sz(S)) ret.eb(rev[lca(S[i-1],S[i])],S[i]);
		return ret;
	}
};
