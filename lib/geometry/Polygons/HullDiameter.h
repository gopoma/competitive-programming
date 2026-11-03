/**
 * Description: Rotating calipers. Devuelve el CUADRADO de la mayor distancia
   * entre dos puntos del conjunto (no hace falta pasarle el hull: lo calcula).
 * Requiere: Point.h, ConvexHull.h
 * Time: O(N) dado el hull, O(N log N) en total
 * Source: KACTL
   * https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/HullDiameter.h
 * Verification: https://open.kattis.com/problems/roberthood
 */

// el parametro se llama ps y no P a proposito: P es el tipo punto
T diameter2(vP ps) {
	ps = hull(ps);
	int n = sz(ps), ind = 1; T ans = 0;
	if (n > 1) F0R(i,n) for (int j = (i+1)%n;;ind = (ind+1)%n) {
		ckmax(ans, abs2(ps[i]-ps[ind]));
		if (cross(ps[j]-ps[i],ps[(ind+1)%n]-ps[ind]) <= 0) break;
	}
	return ans;
}
