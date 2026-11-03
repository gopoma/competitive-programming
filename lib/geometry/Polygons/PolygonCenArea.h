/**
 * Description: Centroide (centro de masa, con densidad constante) y area CON
   * SIGNO de un poligono simple. El signo es positivo si viene en CCW.
   * Para el area a secas: abs(cenArea(v).s).
 * Requiere: Point.h
 * Time: O(N)
 * Source: http://codeforces.com/blog/entry/22175, KACTL
   * https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/PolygonCenArea.h
 * Verification: https://open.kattis.com/problems/polygonarea
 */

// con T = ll las dos divisiones truncan: ahi conviene usar el area*2 a mano
pair<P,T> cenArea(const vP& v) { assert(sz(v) >= 3);
	P cen{}; T area{};
	F0R(i,sz(v)) {
		int j = (i+1)%sz(v); T a = cross(v[i],v[j]);
		cen += a*(v[i]+v[j]); area += a; }
	return {cen/area/(T)3,area/2}; // el area viene CON SIGNO
}
