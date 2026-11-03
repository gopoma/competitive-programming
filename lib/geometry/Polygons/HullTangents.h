/**
 * Description: Tangentes inferior y superior desde un punto estrictamente
   * afuera a un poligono convexo en CCW sin tres puntos colineales (el hull
   * estricto de ConvexHull.h cumple eso). Devuelve los dos indices.
 * Requiere: Point.h
 * Time: O(log N)
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/HullTangents.h
 * Verification: tested
 */

bool lower; // cual de las dos tangentes se esta buscando
bool better(P a, P b, P c) {
	T z = cross(a,b,c);
	return lower ? z < 0 : z > 0; }
int tangent(const vP& a, P b) {
	if (sz(a) == 1) return 0;
	int lo, hi;
	if (better(b,a[0],a[1])) {
		lo = 0, hi = sz(a)-1;
		while (lo < hi) {
			int mid = (lo+hi+1)/2;
			if (better(b,a[0],a[mid])) lo = mid;
			else hi = mid-1;
		}
		lo = 0;
	} else {
		lo = 1, hi = sz(a);
		while (lo < hi) {
			int mid = (lo+hi)/2;
			if (!better(b,a[0],a[mid])) lo = mid+1;
			else hi = mid;
		}
		hi = sz(a);
	}
	while (lo < hi) {
		int mid = (lo+hi)/2;
		if (better(b,a[mid],a[(mid+1)%sz(a)])) lo = mid+1;
		else hi = mid;
	}
	return lo%sz(a);
}
pi tangents(const vP& a, P b) {
	lower = 1; int x = tangent(a,b);
	lower = 0; int y = tangent(a,b);
	return {x,y};
}
