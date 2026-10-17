/**
 * Description: Segment tree with point assignment and range query. T() is the neutral value,
 *   a + b folds two neighbouring intervals (a left of b) and must be associative.
 *   max_right / min_left descend the tree to find a boundary, like the AtCoder Library.
 * Time: O(n) build, O(log n) set, prod, max_right and min_left, O(1) get and all_prod
 * Source: codeforces.com/blog/entry/18051, KACTL. Manual: SegmentTree.md, stress: README.md
 * Public: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/SegmentTree.h
 */

template <class T>
struct SegmentTree {
  public:
    SegmentTree() : SegmentTree(0) {}

    explicit SegmentTree(int len) {
        SZ = 1;

        while(SZ < max(1, len)) {
            SZ *= 2;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, T());                // todo identidad, no hace falta pull:
    }                                           // T() + T() == T()

    explicit SegmentTree(const vector<T>& init) : n(int(init.size())) {
        SZ = 1;

        while(SZ < max(1, n)) {
            SZ *= 2;
        }

        seg.assign(2 * SZ, T());

        for(int i = 0; i < n; i++) {
            seg[SZ + i] = init[i];
        }

        for(int p = SZ - 1; p > 0; p--) {
            pull(p);
        }
    }

    void set(int pos, T val) {
        assert(0 <= pos && pos < n);

        pos += SZ;
        seg[pos] = val;

        for(pos /= 2; pos > 0; pos /= 2) {
            pull(pos);
        }
    }

    T get(int pos) const {
        assert(0 <= pos && pos < n);
        return seg[pos + SZ];
    }

    T all_prod() const {
        return seg[1];
    }

    // Vuelca el arreglo logico para depurar: dump()[i] es exactamente lo que da get(i).
    // Son n elementos, no SZ: el relleno [n, SZ) no es parte del arreglo.
    vector<T> dump() const {
        return vector<T>(seg.begin() + SZ, seg.begin() + SZ + n);
    }

    T prod(int l, int r) const { // zero-indexed, inclusive
        assert(0 <= l && l <= r && r < n);

        T ra = T();
        T rb = T();

        l += SZ;
        r += SZ + 1;

        while(l < r) {
            if(l & 1) {
                ra = ra + seg[l];
                l++;
            }

            if(r & 1) {
                r--;
                rb = seg[r] + rb;
            }

            l /= 2;
            r /= 2;
        }

        return ra + rb;
    }

    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    //
    // Recorre la descomposicion de [l, r] de izquierda a derecha absorbiendo nodos enteros
    // mientras f aguante, y cuando uno rompe baja por el para ubicar la posicion exacta.
    // El nodo actual cubre [pos, pos + len - 1]; ACL no necesita llevar eso porque su
    // version no tiene r, pero con rango acotado hay que AGRANDAR mientras el padre entre
    // y ENCOGER cuando el hermano se pase de r.
    template<class F>
    int max_right(int l, int r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        int k = l + SZ;
        int pos = l;
        int len = 1;
        T sm = T();                             // vale prod(l, pos - 1)

        while(pos <= r) {
            while(k % 2 == 0 && pos + 2 * len - 1 <= r) {
                k >>= 1;                        // agrandar: el padre todavia entra
                len *= 2;
            }

            while(pos + len - 1 > r) {
                k = 2 * k;                      // encoger: este nodo se pasa de r
                len /= 2;
            }

            T t = sm + seg[k];                  // sm a la izquierda, el nodo a la derecha

            if(!pred(t)) {                      // rompe: la respuesta esta adentro
                while(k < SZ) {
                    k = 2 * k;
                    len /= 2;
                    T t2 = sm + seg[k];

                    if(pred(t2)) {              // el izquierdo aguanta: absorber e ir al derecho
                        sm = t2;
                        pos += len;
                        k++;
                    }
                }

                return pos - 1;                 // pos rompe, la ultima buena es pos - 1
            }

            sm = t;                             // aguanta entero: absorber y seguir
            pos += len;
            k++;
        }

        return r;                               // aguanto todo [l, r]
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    // Espejo del de arriba: el nodo cubre [pos - len + 1, pos], se encoge por el lado
    // derecho, y el agregado se arma con el nodo a la IZQUIERDA de lo acumulado.
    template<class F>
    int min_left(int l, int r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        int k = r + SZ;
        int pos = r;
        int len = 1;
        T sm = T();                             // vale prod(pos + 1, r)

        while(pos >= l) {
            while(k % 2 == 1 && k > 1 && pos - 2 * len + 1 >= l) {
                k >>= 1;
                len *= 2;
            }

            while(pos - len + 1 < l) {
                k = 2 * k + 1;                  // encoger por el lado DERECHO
                len /= 2;
            }

            T t = seg[k] + sm;                  // el nodo a la IZQUIERDA de sm

            if(!pred(t)) {
                while(k < SZ) {
                    k = 2 * k + 1;              // el DERECHO primero
                    len /= 2;
                    T t2 = seg[k] + sm;

                    if(pred(t2)) {
                        sm = t2;
                        pos -= len;
                        k--;
                    }
                }

                return pos + 1;
            }

            sm = t;
            pos -= len;
            k--;
        }

        return l;
    }

  private:
    int n = 1;
    int SZ = 1;
    vector<T> seg;

    void pull(int p) {
        seg[p] = seg[2 * p] + seg[2 * p + 1];
    }
};

// /here goes the template!
struct Node {
    // size == 0 es el rango vacio, la identidad de +. pref, suf y best son sumas de
    // subarreglos, y el vacio cuenta, asi que ninguna de las tres baja de cero.
    long long size = 0, sum = 0, pref = 0, suf = 0, best = 0;

    Node() {}
    Node(long long x)
        : size(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}

    friend Node operator+(const Node& a, const Node& b) {
        if(a.size == 0) {
            return b;
        }

        if(b.size == 0) {
            return a;
        }

        Node res;
        res.size = a.size + b.size;
        res.sum = a.sum + b.sum;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suf = max(b.suf, b.sum + a.suf);
        res.best = max(max(a.best, b.best), a.suf + b.pref);  // el que cruza la union
        return res;
    }
};
