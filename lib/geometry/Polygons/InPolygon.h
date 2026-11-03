/**
 * Description: Dice si un punto esta adentro, sobre el borde o afuera de un
   * poligono simple (-1, 0, 1). Sirve con el poligono en CW o en CCW.
   * El borde se detecta con onSeg, o sea con EPS, a diferencia del hull.
 * Requiere: Point.h
 * Time: O(N)
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/InPolygon.h
 * Verification: https://open.kattis.com/problems/pointinpolygon
 */

int inPoly(const P& p, const vP& poly) {
	int n = sz(poly), ans = 0;
	F0R(i,n) {
		P x = poly[i], y = poly[(i+1)%n]; if (x.s > y.s) swap(x,y);
		if (onSeg(p,{x,y})) return 0;
		ans ^= (x.s <= p.s && p.s < y.s && cross(p,x,y) > 0);
	}
	return ans ? -1 : 1;
}
