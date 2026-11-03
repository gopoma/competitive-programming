/**
 * Description: Vertices de la interseccion de semiplanos. Un semiplano es el
   * area a la IZQUIERDA del rayo {p, dp}. La interseccion tiene que ser
   * acotada y de area no nula. El area sale precisa con enteros de hasta 1e5.
 * Requiere: Point.h, AngleCmp.h
 * Time: O(N log N)
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/HalfPlaneIsect.h
 * Verification: https://open.kattis.com/problems/bigbrother
	* https://icpc.kattis.com/problems/domes
	* https://codeforces.com/gym/100962 B
 */

struct Ray {
	P p, dp; // origen, direccion
	P isect(const Ray& L) const {
		return p+dp*(cross(L.dp,L.p-p)/cross(L.dp,dp)); }
	bool operator<(const Ray& L) const {
		return angleCmp(dp,L.dp); }
};

vP halfPlaneIsect(V<Ray> rays, bool add_bounds = false) {
	if (add_bounds) { // acota la entrada con el rectangulo [0,DX] x [0,DY]
		int DX = 1e9, DY = 1e9;
		rays.pb({P{0,0},P{1,0}});
		rays.pb({P{DX,0},P{0,1}});
		rays.pb({P{DX,DY},P{-1,0}});
		rays.pb({P{0,DY},P{0,-1}});
	}
	sor(rays); // ordena los rayos por angulo
	{ // saca los rayos paralelos, dejando el mas restrictivo
		V<Ray> nrays;
		each(t,rays) {
			if (!sz(nrays) || cross(nrays.bk.dp,t.dp) > EPS) { nrays.pb(t); continue; }
			if (cross(t.dp,t.p-nrays.bk.p) > 0) nrays.bk = t;
		}
		swap(rays, nrays);
	}
	auto bad = [&](const Ray& a, const Ray& b, const Ray& c) {
		P p1 = a.isect(b), p2 = b.isect(c);
		if (dot(p2-p1,b.dp) <= EPS) { // este EPS hace falta
			if (cross(a.dp,c.dp) <= 0) return 2; // isect(a,b,c) vacia
			return 1; // isect(a,c) == isect(a,b,c): b no aporta
		}
		return 0; // los tres rayos importan
	};
	// el macro necesita el return {} de la funcion, asi que no puede ser lambda
	#define reduce(t) \
		while (sz(poly) > 1) { \
			int b = bad(poly.at(sz(poly)-2),poly.bk,t); \
			if (b == 2) return {}; \
			if (b == 1) poly.pop_back(); \
			else break; \
		}
	deque<Ray> poly;
	each(t,rays) { reduce(t); poly.pb(t); }
	// con menos de 3 rayos no hay poligono acotado, y el poly[1] de abajo
	// leeria fuera de rango
	if (sz(poly) < 3) return {};
	for(;;poly.pop_front()) {
		reduce(poly[0]);
		if (!bad(poly.bk,poly[0],poly[1])) break;
	}
	#undef reduce
	assert(sz(poly) >= 3); // se esperaba area no nula
	vP poly_points; F0R(i,sz(poly))
		poly_points.pb(poly[i].isect(poly[(i+1)%sz(poly)]));
	return poly_points;
}
