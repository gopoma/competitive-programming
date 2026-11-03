/**
 * Description: Puntos de interseccion y area de interseccion de dos circulos.
   * Una tangencia se devuelve dos veces (el mismo punto repetido).
 * Requiere: Point.h, Circle.h
 * Source: Own
	* ver tambien http://mathworld.wolfram.com/Circle-CircleIntersection.html
 * Verification:https://codefights.com/tournaments/s8thqrnQL2YPK7XQt/L
 */

vP isect(const Circ& x, const Circ& y) { // precondicion: x!=y
	T d = abs(x.f-y.f), a = x.s, b = y.s;
	if (sgn(d) == 0) { assert(sgn(a-b) != 0); return {}; } // concentricos: x!=y
	// radio 0: x es un punto. Sin esto se divide por a y salen NaN callados.
	if (sgn(a) == 0) return in(y,x.f) == 0 ? vP{x.f,x.f} : vP{};
	T C = (a*a+d*d-b*b)/(2*a*d);
	if (abs(C) > 1+EPS) return {};
	C = max((T)-1,min((T)1,C));
	T S = sqrt(max(1-C*C,(T)0)); P tmp = (y.f-x.f)/d*x.s;
	return {x.f+tmp*P(C,S),x.f+tmp*P(C,-S)};
}
vP isect(const Circ& x, const Line& y) {
	P c = foot(x.f,y); T sq_dist = sq(x.s)-abs2(x.f-c);
	if (sgn(sq_dist) < 0) return {};
	P offset = unit(y.s-y.f)*sqrt(max(sq_dist,T(0)));
	return {c+offset,c-offset};
}
T isect_area(Circ x, Circ y) {
	T d = abs(x.f-y.f), a = x.s, b = y.s; if (a < b) swap(a,b);
	if (d >= a+b) return 0;          // disjuntos o tangentes por fuera
	if (d <= a-b) return PI*b*b;     // y contenido en x (cubre b == 0)
	T ca = (a*a+d*d-b*b)/(2*a*d), cb = (b*b+d*d-a*a)/(2*b*d);
	ca = max((T)-1,min((T)1,ca)); cb = max((T)-1,min((T)1,cb));
	T s = (a+b+d)/2, h = 2*sqrt(max(s*(s-a)*(s-b)*(s-d),(T)0))/d;
	return a*a*acos(ca)+b*b*acos(cb)-d*h;
}
