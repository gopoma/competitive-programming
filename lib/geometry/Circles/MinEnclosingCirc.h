/**
 * Description: Circulo minimo que contiene a todos los puntos.
 * Requiere: Point.h, Circle.h, Circumcenter.h
 * Time: O(N) esperado
 * Source: KACTL
 * Verification: USACO Camp 2019 Contest 2 #4
 */

Circ mec(vP ps) {
	shuffle(all(ps), rng);
	// holgura MULTIPLICATIVA, distinta del EPS aditivo global: no lo tapa
	P o = ps[0]; T r = 0, holgura = 1+1e-8;
	F0R(i,sz(ps)) if (abs(o-ps[i]) > r*holgura) {
		o = ps[i], r = 0; // el punto queda sobre el MEC
		F0R(j,i) if (abs(o-ps[j]) > r*holgura) {
			o = (ps[i]+ps[j])/2, r = abs(o-ps[i]);
			F0R(k,j) if (abs(o-ps[k]) > r*holgura)
				tie(o,r) = ccCenter(ps[i],ps[j],ps[k]);
		}
	}
	return {o,r};
}
