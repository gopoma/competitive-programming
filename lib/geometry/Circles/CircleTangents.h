 /**
 * Description: Tangentes internas y externas entre dos circulos.
 * Requiere: Point.h, Circle.h
 * Source: Own
 * Verification: USACO Laser Cows
 */

P tangent(P x, Circ y, int t = 0) {
	y.s = abs(y.s); // el abs hace falta porque internal() llama con y.s < 0
	if (sgn(y.s) == 0) return y.f;
	T d = abs(x-y.f);
	P a = pow(y.s/d,2)*(x-y.f)+y.f;
	// con x calculado sobre el borde, el redondeo lo deja apenas adentro y la
	// raiz daria nan. Tolerancia RELATIVA: un x realmente adentro sigue en nan
	T h2 = d*d-y.s*y.s; if (h2 < 0 && h2 > -1e-9*d*d) h2 = 0;
	P b = sqrt(h2)/d*y.s*unit(x-y.f)*dir(PI/2);
	return t == 0 ? a+b : a-b;
}
V<pair<P,P>> external(Circ x, Circ y) {
	V<pair<P,P>> v;
	// con radios iguales las tangentes son paralelas; si no, se usa el centro de
	// homotecia. El sgn no es cosmetico: con radios casi iguales y.s-x.s es
	// diminuto y ese centro se va al infinito.
	if (sgn(x.s-y.s) == 0) {
		P tmp = unit(x.f-y.f)*x.s*dir(PI/2);
		v.eb(x.f+tmp,y.f+tmp);
		v.eb(x.f-tmp,y.f-tmp);
	} else {
		P p = (y.s*x.f-x.s*y.f)/(y.s-x.s);
		F0R(i,2) v.eb(tangent(p,x,i),tangent(p,y,i));
	}
	return v;
}
V<pair<P,P>> internal(Circ x, Circ y) {
	return external({x.f,-x.s},y); }
