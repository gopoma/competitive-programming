// Library Checker — Range Kth Smallest
// https://judge.yosupo.jp/problem/range_kth_smallest
//
//   N Q
//   a_0 ... a_{N-1}                      0 <= a_i <= 1e9
//   l r k                                0 <= l < r <= N,  0 <= k < r - l
//   -> el (k+1)-esimo menor de a[l .. r-1]        o sea k viene 0-indexado
//
// La idea: comprimir los valores a [0, m) y construir N+1 versiones de un contador sobre
// el dominio de VALORES, no de posiciones. ver[i] cuenta cuantas veces aparece cada valor
// en a[0 .. i-1]. Entonces
//
//     cuantos elementos de a[l .. r-1] valen v   =   ver[r][v] - ver[l][v]
//
// y eso se extiende a cualquier subarbol: el conteo de un nodo en el rango es la resta de
// ese mismo nodo en las dos versiones. Por eso hace falta bajar por LAS DOS A LA VEZ:
// con una sola version no se puede, y la resta no esta en el contrato del monoide.
//
// max_right de DOS versiones hace exactamente esa bajada: busca la mayor posicion del
// dominio de valores donde el conteo acumulado sigue siendo < k, y el k-esimo es la
// siguiente. La resta va en la lambda, asi que el monoide no necesita inverso.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct NodeSum {                                // NodeSum() vale 0, que ya es la identidad de +
    int sum = 0;

    NodeSum() {}
    NodeSum(int x) : sum(x) {}

    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) {
        return NodeSum(a.sum + b.sum);
    }
};

/**
 * Description: Persistent segment tree. Every set returns the root of a NEW version and a
 *   root is just an int. Pool: max_nodes(n, q) = 2n + (ceil(log2 n) + 1) * q + 1.
 * Time: O(n) build, O(log n) set, get and prod, O(1) all_prod and copy
 * Source: own, after usaco.guide/adv/persistent. Manual: PersistentSegmentTree.md
 */

template <class T>
struct PersistentSegmentTree {
  public:
    PersistentSegmentTree(int len, long long max_ops) : n(len) {
        assert(n >= 1 && max_ops >= 0);

        st.reserve(size_t(max_nodes(n, max_ops)));
        st.push_back(InternalNode());           // el nodo nulo: subarbol entero en T()
    }

    static long long max_nodes(int len, long long max_ops) {
        assert(len >= 1 && max_ops >= 0);
        return 2LL * len + (long long)(ceil_log2(len) + 1) * max_ops + 1;
    }

    int build() {
        return 0;
    }

    int build(const vector<T>& init) {
        assert(int(init.size()) == n);
        return build(0, n - 1, init);
    }

    int set(int root, int pos, T val) {
        assert(valid(root));
        assert(0 <= pos && pos < n);

        return set(root, 0, n - 1, pos, val);
    }

    T get(int root, int pos) const {
        assert(valid(root));
        assert(0 <= pos && pos < n);

        return get(root, 0, n - 1, pos);
    }

    T prod(int root, int l, int r) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        return prod(root, 0, n - 1, l, r);
    }

    T all_prod(int root) const {
        assert(valid(root));
        return st[root].val;
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(rt, l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    int max_right(int root, int l, int r, F pred) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_izq(root, 0, n - 1, l, r, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(rt, p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    int min_left(int root, int l, int r, F pred) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_der(root, 0, n - 1, l, r, acc, pred) + 1;
    }

    // Vuelca el arreglo logico de UNA version: dump(rt)[i] es lo que da get(rt, i).
    // Sirve para mirar cualquier version, incluso vieja, y no consume nodos del pool.
    // Los mismos dos descensos, pero sobre la DIFERENCIA de dos versiones: el arreglo
    // virtual que se recorre es root_after MENOS root_before. f(antes, despues) recibe los dos
    // acumulados y la resta corre por tu cuenta, asi que el monoide no necesita inverso.
    //
    // Sirve para el k-esimo menor de un rango de posiciones: con el arbol sobre el dominio
    // de valores y ver[i] = conteos de a[0..i-1], el rango [l, r) ES la diferencia entre
    // ver[l] y ver[r]. Y el centinela te dice si el k-esimo no existe.
    //
    // PRECONDICION: root_before tiene que ser una sub-version de root_after, o sea que sus
    // agregados no lo superen en ningun nodo. Se cumple solo si los dos salen de la misma
    // cadena de prefijos. Con versiones de ramas distintas la diferencia puede dar negativa
    // y la monotonia de f se rompe en silencio: no hay forma de asertarlo.
    template<class F>
    int max_right(int root_before, int root_after, int l, int r, F pred) const {
        assert(valid(root_before) && valid(root_after));
        assert(0 <= l && l <= r && r < n);

        T acc_before = T(), acc_after = T();
        return corte_izq(root_before, root_after, 0, n - 1, l, r, acc_before, acc_after, pred) - 1;
    }

    template<class F>
    int min_left(int root_before, int root_after, int l, int r, F pred) const {
        assert(valid(root_before) && valid(root_after));
        assert(0 <= l && l <= r && r < n);

        T acc_before = T(), acc_after = T();
        return corte_der(root_before, root_after, 0, n - 1, l, r, acc_before, acc_after, pred) + 1;
    }

    vector<T> dump(int root) const {
        assert(valid(root));

        vector<T> out;
        out.reserve(size_t(n));
        dump(root, 0, n - 1, out);
        return out;
    }

    int copy(int root) {
        assert(valid(root));
        return clone(root);
    }

    int size() const {
        return n;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

  private:
    struct InternalNode {
        int l = 0;
        int r = 0;
        T val{};
    };

    int n;
    vector<InternalNode> st;

    static int ceil_log2(int x) {
        int c = 0;

        while((1 << c) < x) {
            ++c;
        }

        return c;
    }

    bool valid(int rt) const {
        return 0 <= rt && rt < int(st.size());
    }

    // El nodo se arma entero antes de entrar al pool, asi que nunca se lee st[...] con una
    // referencia viva mientras se inserta.
    int new_node(int l, int r, const T& val) {
        InternalNode nd;
        nd.l = l;
        nd.r = r;
        nd.val = val;
        st.push_back(nd);
        return int(st.size()) - 1;
    }

    int clone(int k) {
        return new_node(st[k].l, st[k].r, st[k].val);
    }

    // Los mismos dos, caminando las dos versiones en lockstep. La descomposicion de [l, r]
    // depende del par (lx, rx) de la recursion y no del nodo, asi que bajar por los dos
    // hijos a la vez los mantiene cubriendo el mismo intervalo.
    template<class F>
    int corte_izq(int cur_before, int cur_after, int lx, int rx, int l, int r,
                  T& acc_before, T& acc_after, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar los acumulados
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            T t_before = acc_before + st[cur_before].val;
            T t_after = acc_after + st[cur_after].val;

            if(f(t_before, t_after)) {
                acc_before = t_before;
                acc_after = t_after;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lx == rx) {
                return lx;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        int mx = (lx + rx) / 2;
        int res = corte_izq(st[cur_before].l, st[cur_after].l, lx, mx, l, r,
                            acc_before, acc_after, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur_before].r, st[cur_after].r, mx + 1, rx, l, r,
                         acc_before, acc_after, f);
    }

    template<class F>
    int corte_der(int cur_before, int cur_after, int lx, int rx, int l, int r,
                  T& acc_before, T& acc_after, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            T t_before = st[cur_before].val + acc_before;   // el nodo a la IZQUIERDA
            T t_after = st[cur_after].val + acc_after;

            if(f(t_before, t_after)) {
                acc_before = t_before;
                acc_after = t_after;
                return l - 1;
            }

            if(lx == rx) {
                return lx;
            }
        }

        int mx = (lx + rx) / 2;
        int res = corte_der(st[cur_before].r, st[cur_after].r, mx + 1, rx, l, r,
                            acc_before, acc_after, f);     // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur_before].l, st[cur_after].l, lx, mx, l, r,
                         acc_before, acc_after, f);
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es T(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    template<class F>
    int corte_izq(int cur, int lx, int rx, int l, int r, T& acc, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            T t = acc + st[cur].val;            // acc a la izquierda, el nodo a la derecha
            if(f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lx == rx) {
                return lx;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        int mx = (lx + rx) / 2;
        int res = corte_izq(st[cur].l, lx, mx, l, r, acc, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].r, mx + 1, rx, l, r, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    int corte_der(int cur, int lx, int rx, int l, int r, T& acc, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            T t = st[cur].val + acc;            // el nodo a la IZQUIERDA de acc
            if(f(t)) {
                acc = t;
                return l - 1;
            }

            if(lx == rx) {
                return lx;
            }
        }

        int mx = (lx + rx) / 2;
        int res = corte_der(st[cur].r, mx + 1, rx, l, r, acc, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].l, lx, mx, l, r, acc, f);
    }

    // st[0] es el nodo nulo: sus hijos son 0 y su val ya es T(), asi que un subarbol sin
    // materializar no necesita caso aparte.
    void dump(int cur, int lx, int rx, vector<T>& out) const {
        if(lx == rx) {
            out.push_back(st[cur].val);
            return;
        }

        int mx = (lx + rx) / 2;
        dump(st[cur].l, lx, mx, out);
        dump(st[cur].r, mx + 1, rx, out);
    }

    int build(int lx, int rx, const vector<T>& a) {
        if(lx == rx) {
            return new_node(0, 0, a[lx]);
        }

        int mx = (lx + rx) / 2;
        int lc = build(lx, mx, a);
        int rc = build(mx + 1, rx, a);
        return new_node(lc, rc, st[lc].val + st[rc].val);
    }

    int set(int cur, int lx, int rx, int p, const T& x) {
        if(lx == rx) {
            return new_node(0, 0, x);
        }

        int mx = (lx + rx) / 2;
        int lc = st[cur].l;
        int rc = st[cur].r;

        if(p <= mx) {
            lc = set(lc, lx, mx, p, x);
        } else {
            rc = set(rc, mx + 1, rx, p, x);
        }

        return new_node(lc, rc, st[lc].val + st[rc].val);
    }

    T get(int cur, int lx, int rx, int p) const {
        while(lx != rx) {
            if(cur == 0) {                      // subarbol sin materializar
                return T();
            }

            int mx = (lx + rx) / 2;

            if(p <= mx) {
                cur = st[cur].l;
                rx = mx;
            } else {
                cur = st[cur].r;
                lx = mx + 1;
            }
        }

        return st[cur].val;                     // si cur es 0, st[0].val ya es T()
    }

    T prod(int cur, int lx, int rx, int ql, int qr) const {
        if(cur == 0 || rx < ql || qr < lx) {
            return T();
        }

        if(ql <= lx && rx <= qr) {
            return st[cur].val;
        }

        int mx = (lx + rx) / 2;
        return prod(st[cur].l, lx, mx, ql, qr) + prod(st[cur].r, mx + 1, rx, ql, qr);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for(int& x : a) {
        cin >> x;
    }

    vector<int> vals = a;                       // compresion de coordenadas
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = (int)vals.size();

    // El arbol vive sobre el dominio de VALORES [0, m), no sobre las posiciones.
    // n sets, cada uno cuesta C + 1 nodos; build() sin argumentos cuesta cero.
    PersistentSegmentTree<NodeSum> st(m, n);

    vector<int> ver(n + 1);
    ver[0] = st.build();

    vector<int> veces(m, 0);                    // el conteo corriente, para no leer con get
    for(int i = 0; i < n; i++) {
        int c = int(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());
        ++veces[c];
        ver[i + 1] = st.set(ver[i], c, NodeSum(veces[c]));
    }

    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;

        // La mayor posicion p del dominio de valores tal que en a[l..r-1] hay MENOS de
        // k+1 elementos con valor <= vals[p]. El k-esimo menor es entonces vals[p + 1].
        int faltan = k + 1;                     // el enunciado da k 0-indexado
        int p = st.max_right(ver[l], ver[r], 0, m - 1,
            [&](const NodeSum& antes, const NodeSum& despues) {
                return despues.sum - antes.sum < faltan;
            });

        // El enunciado garantiza k < r - l, asi que el k-esimo siempre existe. Si no fuera
        // asi, p == m - 1 seria exactamente el caso "no hay tantos elementos".
        cout << vals[p + 1] << "\n";
    }

    return 0;
}
