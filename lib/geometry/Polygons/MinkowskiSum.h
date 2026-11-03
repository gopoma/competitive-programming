/**
 * Description: Suma de Minkowski de dos poligonos convexos dados en CCW.
   * El resultado es convexo y tambien queda en CCW.
 * Requiere: Point.h
 * Time: O(N)
 * Source: https://cp-algorithms.com/geometry/minkowski.html#implementation
   * https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/MinkowskiSum.h
 * Verification: https://open.kattis.com/problems/roberthood
 */

// el diameter2 que trae el original esta omitido: lo da HullDiameter.h
vP minkowski_sum(vP a, vP b) {
	if (sz(a) > sz(b)) swap(a, b);
	if (!sz(a)) return {};
	if (sz(a) == 1) {
		each(t, b) t += a.ft;
		return b;
	}
	rotate(begin(a), min_element(all(a)), end(a));
	rotate(begin(b), min_element(all(b)), end(b));
	a.pb(a[0]), a.pb(a[1]);
	b.pb(b[0]), b.pb(b[1]);
	vP result;
	int i = 0, j = 0;
	while (i < sz(a)-2 || j < sz(b)-2) {
		result.pb(a[i]+b[j]);
		T crs = cross(a[i+1]-a[i],b[j+1]-b[j]);
		i += (crs >= 0);
		j += (crs <= 0);
	}
	return result;
}
