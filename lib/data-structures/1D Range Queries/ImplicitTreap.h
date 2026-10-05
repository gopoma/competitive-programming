/**
 * Description: Implicit treap. A vector with O(log n) insert, erase, reverse, rotate, move,
 *   range query and range update. Manual, Node contract and examples: ImplicitTreap.md
 * Time: O(n) build, O(log n) expected rest. Memory: n + q nodes, q = expected inserts
 * Source: own. Verification: stress tested against brute force, see ImplicitTreap.md
 */

struct NoLazy {};                               // marcador: el treap no lleva updates de rango

template <class Node, class LazyUpdate = NoLazy>
struct ImplicitTreap {
  public:
    static constexpr bool HAS_LAZY = !is_same<LazyUpdate, NoLazy>::value;

    explicit ImplicitTreap(long long q) {
        reserve_pool(0, q);
    }

    // gen(i) se llama con i = 0, 1, ..., n - 1 EN ESE ORDEN, y el valor va directo al pool.
    // Asi se puede leer de un stream sin armar ningun vector intermedio.
    template <class F>
    ImplicitTreap(int n, long long q, F gen) {
        assert(n >= 0);
        reserve_pool(n, q);

        for(int i = 0; i < n; i++) {
            new_node(gen(i));                   // el nodo de la posicion i queda en 1 + i
        }

        root = build(0, n - 1);
    }

    ImplicitTreap(const vector<Node>& v, long long q)
        : ImplicitTreap((int)v.size(), q, [&](int i) { return v[i]; }) {}

    static long long max_nodes(long long n, long long q) {
        assert(n >= 0 && q >= 0);
        return n + q;
    }

    int size() const {
        return st[root].sz;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

    static size_t node_bytes() {
        return sizeof(InternalNode);
    }

    void insert(int i, Node x) {
        assert(0 <= i && i <= size());          // i == size() agrega al final
        int a, b;
        split(root, i, a, b);
        root = merge(merge(a, new_node(x)), b);
    }

    void erase(int i) {
        assert(0 <= i && i < size());
        int a, b, c, tmp;
        split(root, i, a, tmp);
        split(tmp, 1, b, c);
        root = merge(a, c);
    }

    void set(int p, Node x) {
        assert(0 <= p && p < size());
        int a, b, c, tmp;
        split(root, p, a, tmp);
        split(tmp, 1, b, c);
        st[b].val = x;
        pull(b);
        root = merge(merge(a, b), c);
    }

    Node get(int p) const {
        assert(0 <= p && p < size());
        return prod(p, p);
    }

    Node prod(int l, int r) const {
        assert(0 <= l && l <= r && r < size());
        Node acc;
        bool has = false;
        prod(root, 0, l, r, LazyUpdate(), false, acc, has);
        return acc;
    }

    Node all_prod() const {
        return st[root].agg;
    }

    void apply(int p, LazyUpdate f) {
        static_assert(HAS_LAZY, "este ImplicitTreap se instancio sin LazyUpdate");
        assert(0 <= p && p < size());
        apply(p, p, f);
    }

    void apply(int l, int r, LazyUpdate f) {
        static_assert(HAS_LAZY, "este ImplicitTreap se instancio sin LazyUpdate");
        assert(0 <= l && l <= r && r < size());
        apply(root, 0, l, r, f);
    }

    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r < size());
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);
        all_rev(b);
        root = merge(merge(a, b), c);
    }

    void rotate(int l, int r, int k) {
        assert(0 <= l && l <= r && r < size());
        int len = r - l + 1;
        assert(0 <= k && k < len);

        if(k == 0) {
            return;
        }

        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, len, b, c);
        int b1, b2;
        split(b, k, b1, b2);
        root = merge(merge(a, merge(b2, b1)), c);
    }

    // Corta a[l..r] y lo pega justo antes del que era a[p]. p se cuenta sobre el arreglo
    // ORIGINAL, y tiene que caer afuera del bloque que se mueve.
    void move(int l, int r, int p) {
        assert(0 <= l && l <= r && r < size());
        assert(0 <= p && p <= size() && (p <= l || p > r));
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);
        int rest = merge(a, c);
        int dest = (p <= l) ? p : p - (r - l + 1);
        int x, y;
        split(rest, dest, x, y);
        root = merge(merge(x, b), y);
    }

  private:
    struct InternalNode {
        int lc = 0;
        int rc = 0;
        unsigned pri = 0;
        int sz = 1;
        Node val{};                             // el elemento propio, cubre 1 posicion
        Node agg{};                             // el agregado del subarbol, cubre sz posiciones
        bool rev = false;
        LazyUpdate lz{};                        // si es NoLazy, entra en el relleno: 0 bytes
    };

    vector<InternalNode> st;
    int root = 0;
    unsigned rng = next_seed();             // ver next_seed(): semilla del reloj, no fija

    void reserve_pool(long long n, long long q) {
        assert(n >= 0 && q >= 0);
        st.reserve(size_t(max_nodes(n, q)) + 1);
        st.push_back(InternalNode());           // el nodo nulo
        st[0].sz = 0;
    }

    //? Para Codeforces, o cualquier lugar donde puedan hackearte: la semilla sale del reloj.
    //? Con una semilla fija las prioridades son identicas en cada corrida, y un atacante que
    //? conoce la secuencia puede elegir las posiciones de insert para hacer el arbol profundo.
    //? Medido: un hill climbing de 3000 evaluaciones duplica la profundidad.
    //? Para depurar con una corrida reproducible, descomenta esto:
    // #define IMPLICIT_TREAP_SEED 2463534242u
    static unsigned next_seed() {
#ifdef IMPLICIT_TREAP_SEED
        static unsigned s = IMPLICIT_TREAP_SEED;
#else
        static unsigned s =
            (unsigned)chrono::high_resolution_clock::now().time_since_epoch().count() | 1u;
#endif
        s ^= s << 13;                           // xorshift32 nunca sale de los no nulos,
        s ^= s >> 17;                           // asi que el | 1u alcanza para no quedar en 0
        s ^= s << 5;
        return s;
    }

    unsigned next_pri() {                       // xorshift: no depende de <random>
        rng ^= rng << 13;
        rng ^= rng >> 17;
        rng ^= rng << 5;
        return rng;
    }

    int new_node(const Node& x) {
        InternalNode t;
        t.pri = next_pri();
        t.val = x;
        t.agg = x;
        st.push_back(t);
        return (int)st.size() - 1;
    }

    // Los nodos de las posiciones 0..n-1 ya estan en el pool, en los indices 1..n y EN ORDEN,
    // asi que solo hay que enlazarlos balanceado. Eso no cumple la propiedad de heap, y medido
    // no importa: tras cualquier carga real la profundidad converge a la de un treap aleatorio,
    // y arrancar balanceado es mas chato que arrancar con el arbol cartesiano de las prioridades.
    int build(int lo, int hi) {
        if(lo > hi) {
            return 0;
        }

        int mid = lo + (hi - lo) / 2;
        int t = 1 + mid;
        st[t].lc = build(lo, mid - 1);
        st[t].rc = build(mid + 1, hi);
        pull(t);
        return t;
    }

    // Saltea los subarboles vacios, asi operator+ nunca recibe Node() y el usuario no necesita
    // identidad ni guardas de rango vacio.
    void pull(int t) {
        st[t].sz = 1 + st[st[t].lc].sz + st[st[t].rc].sz;
        Node a = st[t].val;

        if(st[t].lc) {
            a = st[st[t].lc].agg + a;
        }

        if(st[t].rc) {
            a = a + st[st[t].rc].agg;
        }

        st[t].agg = a;
    }

    // El arbol es la autoridad del largo: 1 para el elemento propio, sz para el agregado.
    void all_apply(int t, const LazyUpdate& f) {
        if(!t) {
            return;
        }

        if constexpr (HAS_LAZY) {
            st[t].val.apply(f, 1);
            st[t].agg.apply(f, st[t].sz);
            st[t].lz *= f;
        }
    }

    // El flag queda pendiente para los HIJOS: los hijos de t ya quedan en el orden correcto.
    void all_rev(int t) {
        if(!t) {
            return;
        }

        st[t].rev = !st[t].rev;
        swap(st[t].lc, st[t].rc);
        st[t].agg.reverse();
    }

    void push(int t) {
        if constexpr (HAS_LAZY) {                // incondicional, como en LazySegmentTree
            all_apply(st[t].lc, st[t].lz);
            all_apply(st[t].rc, st[t].lz);
            st[t].lz = LazyUpdate();
        }

        if(st[t].rev) {
            all_rev(st[t].lc);
            all_rev(st[t].rc);
            st[t].rev = false;
        }
    }

    void split(int t, int k, int& a, int& b) {   // los primeros k van a 'a'
        if(!t) {
            a = b = 0;
            return;
        }

        push(t);

        if(st[st[t].lc].sz + 1 <= k) {
            a = t;
            split(st[t].rc, k - st[st[t].lc].sz - 1, st[a].rc, b);
            pull(a);
        } else {
            b = t;
            split(st[t].lc, k, a, st[b].lc);
            pull(b);
        }
    }

    int merge(int a, int b) {
        if(!a || !b) {
            return a ? a : b;
        }

        if(st[a].pri > st[b].pri) {
            push(a);
            st[a].rc = merge(st[a].rc, b);
            pull(a);
            return a;
        }

        push(b);
        st[b].lc = merge(a, st[b].lc);
        pull(b);
        return b;
    }

    static void join(Node& acc, bool& has, const Node& x) {
        if(has) {
            acc = acc + x;
        } else {
            acc = x;
            has = true;
        }
    }

    // Descenso de lectura pura: lo pendiente viaja en f y en rv, no se escribe nada. Por eso
    // una consulta no reestructura ni ensucia el arbol.
    void prod(int t, int lo, int l, int r, LazyUpdate f, bool rv, Node& acc, bool& has) const {
        if(!t) {
            return;
        }

        int hi = lo + st[t].sz - 1;

        if(hi < l || r < lo) {
            return;                             // disjunto
        }

        if(l <= lo && hi <= r) {
            Node piece = st[t].agg;

            if(rv) {
                piece.reverse();                // el subarbol esta logicamente al reves
            }

            if constexpr (HAS_LAZY) {
                piece.apply(f, st[t].sz);
            }

            join(acc, has, piece);
            return;
        }

        LazyUpdate down = st[t].lz;

        if constexpr (HAS_LAZY) {
            down *= f;                          // el lz del nodo primero, el carry despues
        }

        // rv es el flag ENTRANTE: dice si los hijos de t estan dados vuelta
        int fst = rv ? st[t].rc : st[t].lc;
        int snd = rv ? st[t].lc : st[t].rc;
        bool rv2 = rv != st[t].rev;              // esto baja
        int mp = lo + st[fst].sz;

        prod(fst, lo, l, r, down, rv2, acc, has);

        if(l <= mp && mp <= r) {
            Node own = st[t].val;

            if constexpr (HAS_LAZY) {
                own.apply(f, 1);                 // el propio usa f, no down
            }

            join(acc, has, own);
        }

        prod(snd, mp + 1, l, r, down, rv2, acc, has);
    }

    void apply(int t, int lo, int l, int r, const LazyUpdate& f) {
        if(!t) {
            return;
        }

        int hi = lo + st[t].sz - 1;

        if(hi < l || r < lo) {
            return;
        }

        if(l <= lo && hi <= r) {
            all_apply(t, f);
            return;
        }

        push(t);                                 // aca si hay que empujar: vamos a escribir
        int mp = lo + st[st[t].lc].sz;
        apply(st[t].lc, lo, l, r, f);

        if(l <= mp && mp <= r) {
            st[t].val.apply(f, 1);
        }

        apply(st[t].rc, mp + 1, l, r, f);
        pull(t);
    }
};
