/**
 * Description: Dados N puntos, devuelve hasta 4N aristas que contienen un MST
   * del grafo con peso w(p,q) = |p.x-q.x| + |p.y-q.y|.
   * Las aristas vienen como {dist, {src, dst}}, con dist en long long.
 * Time: O(N log N)
 * Source: KACTL
 	* https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * Verification: https://open.kattis.com/problems/gridmst
 */

// despues corre un MST cualquiera (Kruskal + DSU) sobre el resultado
// las sumas y distancias van en long long: con coordenadas de 1e9 un int desborda
V<pair<ll,pi>> manhattanMst(vpi v) {
	vi id(sz(v)); iota(all(id),0);
	V<pair<ll,pi>> ed;
	F0R(k,4) {
		sort(all(id),[&](int i, int j) {
			return (ll)v[i].f+v[i].s < (ll)v[j].f+v[j].s; });
		map<int,int> sweep; // busca vecinos en el primer octante
		each(i,id) { // los que estan en sweep todavia no encontraron vecino
			for (auto it = sweep.lb(-v[i].s);
				it != end(sweep); sweep.erase(it++)) {
				int j = it->s;
				pair<ll,ll> d{(ll)v[i].f-v[j].f,(ll)v[i].s-v[j].s};
				if (d.s>d.f) break;
				ed.pb({d.f+d.s,{i,j}});
			}
			sweep[-v[i].s] = i;
		}
		each(p,v) {
			if (k&1) p.f *= -1;
			else swap(p.f,p.s);
		}
	}
	return ed;
}
