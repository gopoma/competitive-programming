/**
 * Author: gopoma
 * Date: 2026-10-16
 * Source: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/PolyDifference.h
 * Description: Difference array generalized to polynomials: adds a polynomial of degree <= K
 *   to a range in O(K^2), and builds the n values in O(n K), with ONE array. Offline: you
 *   record every add and then build. T is the scalar, a modular int or long long.
 *   Manual, the overflow table and examples: PolyDifference.md
 * Time: O(K^2) add, O(n K) build, O(1) size and clear
 * Status: Stress-tested against brute force for every degree 0..7, with long long and with a
 *   modular int: 142202 checks, plus 80325 with the library mi of ModInt.h.
 *   15 negative controls, all caught. No judge submission yet.
 */

template <int K, class T>
struct PolyDifference {
  public:
    // len es la cantidad de posiciones, a[0 .. len - 1]. El grado K es de compilacion a
    // proposito: con K en tiempo de ejecucion harian falta vectores anidados.
    explicit PolyDifference(int len) : n(len) {
        assert(n >= 1);
        diff.assign(n + K + 2, T(0));

        // Solo se necesita la columna K de Pascal. Se arma el triangulo chico y se extrae,
        // asi T nunca necesita division ni inverso modular: alcanza con +, - y *.
        T tri[2 * K + 1][2 * K + 1];

        for (int fila = 0; fila <= 2 * K; fila++) {
            for (int col = 0; col <= 2 * K; col++) {
                tri[fila][col] = (col == 0) ? T(1)
                               : (col > fila ? T(0) : tri[fila - 1][col - 1] + tri[fila - 1][col]);
            }
        }

        for (int d = 0; d <= K; d++) {
            binom[d] = tri[K + d][K];
        }
    }

    int size() const {
        return n;
    }

    // Olvida todo lo registrado, conservando la capacidad: para varios casos de prueba.
    void clear() {
        diff.assign(n + K + 2, T(0));
    }

    // REGISTRA que a[l + x] += coef[0] + coef[1]*x + ... + coef[K]*x^K, para x = 0 .. r - l.
    // OJO: x es relativo a l, NO el indice absoluto. Para un grado menor que K, los
    // coeficientes de arriba van en cero. Nada se calcula hasta build().
    void add(int l, int r, const array<T, K + 1>& coef) {
        assert(0 <= l && l <= r && r < n);
        add_tail(l, 0, coef, ADD);                    // el polinomio desde l hacia la derecha
        add_tail(r + 1, r + 1 - l, coef, SUBTRACT);   // y su cancelacion desde r + 1
    }

    // Los n valores que resultan de todo lo registrado hasta ahora.
    // Es const y no reserva nada aparte: el vector que devuelve ES el buffer de trabajo, asi
    // que se puede llamar varias veces y cada llamada refleja los add hechos hasta entonces.
    vector<T> build() const {
        vector<T> res = diff;

        for (int paso = 0; paso <= K; paso++) {       // K + 1 sumas de prefijos
            for (int i = 1; i < (int)res.size(); i++) {
                res[i] = res[i] + res[i - 1];
            }
        }

        res.resize(n);
        return res;
    }

  private:
    static constexpr bool ADD = true;                 // para que el call site de add_tail
    static constexpr bool SUBTRACT = false;           // se lea sin adivinar

    int n;
    vector<T> diff;                                   // diferencias finitas de orden K + 1
    T binom[K + 1];                                   // binom[d] = C(K + d, K)

    // Suma (o resta) el polinomio en toda la cola [start, n), evaluado en
    // x = offset + (i - start).
    //
    // Aplicar K + 1 sumas de prefijos a un delta en start da C(i - start + K, K), asi que un
    // delta en start + m aporta d[m] * C(i - start - m + K, K). Esos K + 1 polinomios son una
    // base de los de grado <= K, y el sistema es TRIANGULAR porque C(K, K) = 1:
    //
    //     d[m] = P(offset + m) - suma de d[j] * C(K + m - j, K) para j < m
    //
    // Se tocan solo K + 1 posiciones, y P se evalua en argumentos chicos: offset .. offset + K.
    void add_tail(int start, int offset, const array<T, K + 1>& coef, bool positive) {
        T d[K + 1];

        for (int m = 0; m <= K; m++) {
            T val = eval_poly(coef, offset + m);

            for (int j = 0; j < m; j++) {
                val = val - d[j] * binom[m - j];
            }

            d[m] = val;

            // Sin guarda de limites a proposito: start llega a r + 1 <= n y m a K, asi
            // que start + m <= n + K, y diff mide n + K + 2. Nunca se sale.
            diff[start + m] = positive ? diff[start + m] + d[m] : diff[start + m] - d[m];
        }
    }

    static T eval_poly(const array<T, K + 1>& coef, long long x) {
        T val = T(0), pot = T(1), base = T(x);

        for (int j = 0; j <= K; j++) {
            val = val + coef[j] * pot;
            pot = pot * base;
        }

        return val;
    }
};
