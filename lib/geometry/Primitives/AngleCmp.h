/**
 * Description: Ordena puntos en sentido antihorario alrededor del origen, igual
   * que atan2: el rango es (-pi,pi], asi que el eje x negativo queda al final.
 * Requiere: Point.h
 * Verification: https://codeforces.com/contest/1284/submission/68175790
   * https://codeforces.com/contest/1284/submission/68207607
   * (no uses atan2, pasan cosas raras!)
 * Usage: vP v; sort(all(v),angleCmp);
 */

// WARNING: si lo escribes como bool en vez de int, los resultados son incorrectos
// -1 semiplano inferior y eje x positivo, 0 origen, 1 semiplano superior y eje x negativo
int half(P x) { return sgn(x.s) != 0 ? sgn(x.s) : -sgn(x.f); }
bool angleCmp(P a, P b) { int A = half(a), B = half(b);
	return A == B ? sgn(cross(a,b)) > 0 : A < B; }

// equivale a: sort(all(v),[](P a, P b) {
//    return atan2(a.s,a.f) < atan2(b.s,b.f); });
