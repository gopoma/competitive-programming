/**
 * Description: lineHull recibe una recta y un convexo en CCW. Si todos los
   * vertices caen del mismo lado, devuelve {+-1, vertices mas cercanos a la
   * recta}; si no, {0, rango de vertices que quedan sobre o debajo}.
   * extrVertex da el vertice de maxima proyeccion sobre una direccion.
 * Requiere: Point.h
 * Time: O(log N)
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/LineHullIntersection.h
   * https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/LineHull.h
 * Verification: tested
 */

// el original define Line como AR<P,2>; aca se usa el Line = pair<P,P> de
// Point.h, asi se combina con lineIsect, segDist y onSeg sin convertir nada
#define cmp(i,j) sgn(-dot(nrm,poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i+1,i) >= 0 && cmp(i,i-1+n) < 0
int extrVertex(const vP& poly, P nrm) { // nrm, no dir: dir() es una funcion
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo+1 < hi) {
		int m = (lo+hi)/2;
		if (extr(m)) return m;
		int ls = cmp(lo+1,lo), ms = cmp(m+1,m);
		(ls < ms || (ls == ms && ls == cmp(lo,m)) ? hi : lo) = m;
	}
	return lo;
}
vi same(Line line, const vP& poly, int a) {
	// los vertices que estan en la misma paralela que a
	int n = sz(poly); P nrm = perp(line.f-line.s);
	if (cmp(a+n-1,a) == 0) return {(a+n-1)%n,a};
	if (cmp(a,a+1) == 0) return {a,(a+1)%n};
	return {a};
}
#undef extr
#undef cmp
#define cmpL(i) sgn(cross(line.f,line.s,poly[i]))
pair<int,vi> lineHull(Line line, const vP& poly) {
	int n = sz(poly); assert(n>1);
	int endA = extrVertex(poly,perp(line.f-line.s)); // el mas bajo
	if (cmpL(endA) >= 0) return {1,same(line,poly,endA)};
	int endB = extrVertex(poly,perp(line.s-line.f)); // el mas alto
	if (cmpL(endB) <= 0) return {-1,same(line,poly,endB)};
	AR<int,2> res;
	F0R(i,2) {
		int lo = endA, hi = endB; if (hi < lo) hi += n;
		while (lo < hi) {
			int m = (lo+hi+1)/2;
			if (cmpL(m%n) == cmpL(endA)) lo = m;
			else hi = m-1;
		}
		res[i] = lo%n; swap(endA,endB);
	}
	if (cmpL((res[0]+1)%n) == 0) res[0] = (res[0]+1)%n;
	return {0,{(res[1]+1)%n,res[0]}};
}
#undef cmpL
