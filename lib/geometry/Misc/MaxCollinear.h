/**
 * Description: Maxima cantidad de puntos que caen sobre una misma recta.
   * Precondicion: no hay dos puntos iguales (el assert lo verifica).
 * Time: O(n^2 log n), razonable hasta n ~ 2000
 * Source: own
 * Verification: https://open.kattis.com/problems/maxcolinear
 */

// recta por a y b como {direccion normalizada, desplazamiento}
// el desplazamiento va en long long: con coordenadas de 1e5 ya desborda un int
pair<pi,ll> getline(pi a, pi b) {
	pi z = {b.f-a.f,b.s-a.s};
	assert(z.f != 0 || z.s != 0); // dos puntos iguales: gcd(0,0) == 0 y se divide por 0
	swap(z.f,z.s); z.f *= -1;
	int g = gcd(z.f,z.s); z.f /= g, z.s /= g;
	ckmin(z,{-z.f,-z.s});
	return {z,(ll)z.f*a.f+(ll)z.s*a.s};
}

int solve(vpi p) {
	int n = sz(p);
	map<pair<pi,ll>,int> m;
	F0R(i,n) FOR(j,i+1,n) ++m[getline(p[i],p[j])];
	int mx = 0; each(a,m) ckmax(mx,a.s);
	// una recta con k puntos aporta C(k,2) pares: se invierte para recuperar k
	int ans = 0; FOR(i,1,n+1) if (i*(i-1)/2 <= mx) ans = i;
	return ans;
}
