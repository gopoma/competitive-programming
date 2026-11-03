/**
 * Description: Circulo como {centro,radio}.
 * Requiere: Point.h
 * Source: Own
 * Verification: ver interseccion de circulos
 */

using Circ = pair<P,T>;
int in(const Circ& x, const P& y) { // -1 adentro, 0 en el borde, 1 afuera
	return sgn(abs(y-x.f)-x.s); }
T arcLength(const Circ& x, P a, P b) {
	// precondicion: a y b estan sobre x
	// el clamp evita NaN cuando el redondeo deja |d.f| apenas arriba de 1
	P d = (a-x.f)/(b-x.f);
	return x.s*acos(max((T)-1,min((T)1,d.f))); }
