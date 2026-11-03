/**
 * Description: Convex hull por cadena monotona, en orden CCW. Hull ESTRICTO:
   * descarta los puntos colineales del borde. Usa cross exacto, sin EPS, asi
   * que esta pensado para coordenadas enteras.
 * Requiere: Point.h
 * Time: O(N log N)
 * Source: Wikibooks, KACTL
   * https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/ConvexHull%20(13.2).h
 * Verification: https://open.kattis.com/problems/convexhull
 */

// OJO: ConvexHullGraham.h define el mismo hullInd. Son alternativas, no se pegan juntos.
pair<vi,vi> ulHull(const vP& v) {
	vi p(sz(v)), u, l; iota(all(p), 0);
	sort(all(p), [&v](int a, int b) { return v[a] < v[b]; });
	// agrega i a la cadena C sacando los vertices que dejaron de ser extremos.
	// signo = 1 para la cadena de arriba, -1 para la de abajo. El cross va
	// crudo, sin sgn: este hull es exacto, no tolerante a EPS.
	auto add = [&](vi& C, int i, T signo) {
		while (sz(C) > 1 && signo*cross(v[C[sz(C)-2]],v[C.bk],v[i]) >= 0)
			C.pop_back();
		C.pb(i);
	};
	each(i,p) { add(u,i,1); add(l,i,-1); }
	return {u,l};
}
vi hullInd(const vP& v) { // indices en orden CCW
	vi u,l; tie(u,l) = ulHull(v); if (sz(l) <= 1) return l;
	if (v[l[0]] == v[l[1]]) return {0}; // todos los puntos coinciden
	l.insert(end(l),1+rall(u)-1); return l;
}
vP hull(const vP& v) {
	vi w = hullInd(v); vP res; each(t,w) res.pb(v[t]);
	return res; }
