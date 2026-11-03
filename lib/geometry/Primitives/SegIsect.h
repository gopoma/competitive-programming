/**
 * Description: Punto(s) de interseccion de las rectas (o segmentos) a y b.
 * Requiere: Point.h
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/segmentintersection
 */

// {punto unico de interseccion} si existe
// {b.f,b.s} si las rectas son la misma
// vacio si las rectas no se cortan (paralelas)
vP lineIsect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s);
	// con sgn y no con ==: si T es db, a0 y a1 nunca son exactamente iguales
	if (sgn(a0-a1) == 0) return sgn(a0) == 0 ? vP{b.f,b.s} : vP{};
	return {(b.s*a0-b.f*a1)/(a0-a1)};
}

// point in interior of both segments a and b, if it exists
vP strictIsect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s);
	T b0 = cross(b.f,b.s,a.f), b1 = cross(b.f,b.s,a.s);
	if (sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0)
		return {(b.s*a0-b.f*a1)/(a0-a1)};
	return {};
}

// intersection of segments, a and b may be degenerate
vP segIsect(const Line& a, const Line& b) {
	vP v = strictIsect(a,b); if (sz(v)) return v;
	set<P> s;
	#define i(x,y) if (onSeg(x,y)) s.ins(x)
	i(a.f,b); i(a.s,b); i(b.f,a); i(b.s,a);
	return {all(s)};
}
