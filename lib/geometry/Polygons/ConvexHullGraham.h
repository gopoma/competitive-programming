/**
 * Description: Convex hull por Graham scan, en orden CCW. Hull ESTRICTO:
   * descarta los puntos colineales del borde.
 * Requiere: Point.h
 * Time: O(N log N)
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/ConvexHullGraham.h
 * Verification: https://open.kattis.com/problems/convexhull
 */

// OJO: ConvexHull.h define el mismo hullInd. Son alternativas, no se pegan juntos.
// Con coordenadas enteras conviene T = ll: los cross quedan exactos.
vi hullInd(const vP& v) {
	int ind = int(min_element(all(v))-begin(v));
	vi cand, C{ind}; F0R(i,sz(v)) if (v[i] != v[ind]) cand.pb(i);
	sort(all(cand),[&](int a, int b) {
		// por angulo, y a igual angulo el mas cercano primero
		P x = v[a]-v[ind], y = v[b]-v[ind]; T t = cross(x,y);
		return sgn(t) != 0 ? t > 0 : abs2(x) < abs2(y); });
	each(c,cand) {
		while (sz(C) > 1 && cross(v[end(C)[-2]],v[C.bk],v[c]) <= 0)
			C.pop_back();
		C.pb(c); }
	return C;
}
vP hull(const vP& v) {
	vi w = hullInd(v); vP res; each(t,w) res.pb(v[t]);
	return res; }
