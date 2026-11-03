/**
 * Description: Devuelve {circuncentro,circunradio} del triangulo abc.
 * Requiere: Point.h, Circle.h
 * Source: EGMO
 * Verification: ver MEC
 */

Circ ccCenter(P a, P b, P c) {
	b -= a; c -= a;
	// el denominador es -2i*cross(b,c): se anula si abc son colineales o hay
	// dos puntos iguales. Sin el assert el circuncentro sale NaN en silencio.
	P den = b*conj(c)-conj(b)*c;
	assert(sgn(abs(den)) != 0);
	P res = b*c*(conj(c)-conj(b))/den;
	return {a+res,abs(res)};
}
