/**
 * Description: Implicit treap. A vector with O(log n) insert, erase, reverse, rotate, move,
 *   range query and range update. max_right / min_left descend to find a boundary.
 *   Manual, Node contract and examples: ImplicitTreap.md
 * Time: O(n) build, O(log n) expected rest. Memory: n + q nodes, q = expected inserts
 * Source: own. Verification: judge.yosupo.jp/submission/407984 (Range Reverse Range Sum, 303 ms)
 *   plus 56M brute-force checks and 21 negative controls on the max_right / min_left descent
 * Public: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/ImplicitTreap.h
 */

struct NoLazy {};                               // marcador: el treap no lleva updates de rango

template <class Node, class LazyUpdate = NoLazy>
struct ImplicitTreap {
  public:
    static constexpr bool HAS_LAZY = !is_same<LazyUpdate, NoLazy>::value;

    explicit ImplicitTreap(long long max_ops) {
        reserve_pool(0, max_ops);
    }

    // gen(i) se llama con i = 0, 1, ..., n - 1 EN ESE ORDEN, y el valor va directo al pool.
    // Asi se puede leer de un stream sin armar ningun vector intermedio.
    template <class F>
    ImplicitTreap(int len, long long max_ops, F gen) {
        assert(len >= 0);
        reserve_pool(len, max_ops);

        for(int i = 0; i < len; i++) {
            new_node(gen(i));                   // el nodo de la posicion i queda en 1 + i
        }

        root = build(1, 0, len - 1);
    }

    ImplicitTreap(const vector<Node>& init, long long max_ops)
        : ImplicitTreap((int)init.size(), max_ops, [&](int i) { return init[i]; }) {}

    static long long max_nodes(long long len, long long max_ops) {
        assert(len >= 0 && max_ops >= 0);
        return len + max_ops;
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

    // Vacia el treap conservando la capacidad del pool, asi un problema con varios casos de
    // prueba no vuelve a reservar. Los nodos viejos no se reciclan, igual que con erase.
    void clear() {
        st.resize(1);                           // resize hacia abajo no libera capacidad
        root = 0;
    }

    void insert(int pos, Node val) {
        assert(0 <= pos && pos <= size());      // pos == size() agrega al final
        int a, b;
        split(root, pos, a, b);
        root = merge(merge(a, new_node(val)), b);
    }

    // Inserta toda la secuencia v antes de la que era a[i], en O(|v| + log n): arma un treap
    // balanceado con los nuevos y hace un solo merge. Con insert(i, x) repetido seria
    // O(|v| log n). Cuenta como |v| inserciones para el pool, no como una.
    void insert(int pos, const vector<Node>& block) {
        assert(0 <= pos && pos <= size());

        if(block.empty()) {
            return;
        }

        int base = (int)st.size();              // los nuevos van a base .. base + |block| - 1

        for(const Node& x : block) {
            new_node(x);
        }

        int mid = build(base, 0, (int)block.size() - 1);
        int a, b;
        split(root, pos, a, b);
        root = merge(merge(a, mid), b);
    }

    void push_back(Node val) {
        insert(size(), val);
    }

    void push_front(Node val) {
        insert(0, val);
    }

    void erase(int pos) {
        assert(0 <= pos && pos < size());
        int a, b, c, tmp;
        split(root, pos, a, tmp);
        split(tmp, 1, b, c);
        root = merge(a, c);
    }

    // Borra todo a[l..r] de una vez, en O(log n). Hacerlo con erase(i) repetido seria
    // O(L log n). Los nodos del bloque quedan huerfanos en el pool y no se reciclan: eso ya
    // pasa con erase(i), pero con rangos se nota mas. No afecta a max_nodes, que cuenta
    // elementos insertados, no borrados.
    void erase(int l, int r) {
        assert(0 <= l && l <= r && r < size());
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);            // b es el bloque a descartar
        (void)b;
        root = merge(a, c);
    }

    void pop_back() {
        assert(size() > 0);
        erase(size() - 1);
    }

    void pop_front() {
        assert(size() > 0);
        erase(0);
    }

    void set(int pos, Node val) {
        assert(0 <= pos && pos < size());
        int a, b, c, tmp;
        split(root, pos, a, tmp);
        split(tmp, 1, b, c);
        st[b].val = val;
        pull(b);
        root = merge(merge(a, b), c);
    }

    Node get(int pos) const {
        assert(0 <= pos && pos < size());
        return prod(pos, pos);
    }

    Node front() const {
        assert(size() > 0);
        return get(0);
    }

    Node back() const {
        assert(size() > 0);
        return get(size() - 1);
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

    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que pred(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. pred tiene que ser T T T F F F al crecer p.
    // Ojo: el p vale para el estado de AHORA. Un insert o un erase corre los indices.
    template <class F>
    int max_right(int l, int r, F pred) const {
        assert(0 <= l && l <= r && r < size());

        Node acc;
        bool has = false;
        return corte_izq(root, 0, l, r, LazyUpdate(), false, acc, has, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que pred(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. pred tiene que ser T T T F F F al DECRECER p.
    template <class F>
    int min_left(int l, int r, F pred) const {
        assert(0 <= l && l <= r && r < size());

        Node acc;
        bool has = false;
        return corte_der(root, 0, l, r, LazyUpdate(), false, acc, has, pred) + 1;
    }

    // Toda la secuencia en orden, en O(n). Con get(p) repetido seria O(n log n): medido,
    // 0.047 s contra 0.005 s a n = 5e5. Util para imprimir el arreglo final y para depurar.
    vector<Node> dump() const {
        vector<Node> res;

        if(size() == 0) {
            return res;
        }

        return copy_range(0, size() - 1);
    }

    // Los valores de a[l..r], en O(r - l + log n). Se compone con insert para duplicar un
    // bloque: t.insert(j, t.copy_range(l, r)).
    vector<Node> copy_range(int l, int r) const {
        assert(0 <= l && l <= r && r < size());
        vector<Node> res;
        res.reserve((size_t)(r - l + 1));
        collect(root, 0, l, r, LazyUpdate(), false, res);
        return res;
    }

    void apply(int pos, LazyUpdate upd) {
        static_assert(HAS_LAZY, "este ImplicitTreap se instancio sin LazyUpdate");
        assert(0 <= pos && pos < size());
        apply(pos, pos, upd);
    }

    void apply(int l, int r, LazyUpdate upd) {
        static_assert(HAS_LAZY, "este ImplicitTreap se instancio sin LazyUpdate");
        assert(0 <= l && l <= r && r < size());
        apply(root, 0, l, r, upd);
    }

    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r < size());
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);
        all_rev(b);
        root = merge(merge(a, b), c);
    }

    // Rota a[l..r] a la IZQUIERDA en shift: el viejo a[l+shift] pasa a ser a[l]. Acepta
    // cualquier valor y lo normaliza: negativo rota a la derecha, y un multiplo del largo no
    // hace nada. Es long long para que un valor grande no se estreche antes de entrar aca.
    void rotate(int l, int r, long long shift) {
        assert(0 <= l && l <= r && r < size());
        int len = r - l + 1;
        int k = int(((shift % len) + len) % len);   // la cuenta va en long long; k en [0, len)

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

    // Corta a[l..r] y lo pega justo antes del que era a[to]. to se cuenta sobre el arreglo
    // ORIGINAL, y tiene que caer afuera del bloque que se mueve.
    void move(int l, int r, int to) {
        assert(0 <= l && l <= r && r < size());
        assert(0 <= to && to <= size() && (to <= l || to > r));
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);
        int rest = merge(a, c);
        int dest = (to <= l) ? to : to - (r - l + 1);
        int x, y;
        split(rest, dest, x, y);
        root = merge(merge(x, b), y);
    }

    // Intercambia dos bloques DISJUNTOS, que tienen que venir ordenados: l1 <= r1 < l2 <= r2.
    // Pueden ser adyacentes (r1 + 1 == l2) y de largos distintos.
    void swap_blocks(int l1, int r1, int l2, int r2) {
        assert(0 <= l1 && l1 <= r1 && r1 < l2 && l2 <= r2 && r2 < size());
        int A, B1, C, B2, D, t1, t2, t3;
        split(root, l1, A, t1);                 // A  = [0, l1)
        split(t1, r1 - l1 + 1, B1, t2);         // B1 = [l1, r1]
        split(t2, l2 - r1 - 1, C, t3);          // C  = (r1, l2)
        split(t3, r2 - l2 + 1, B2, D);          // B2 = [l2, r2],  D = (r2, n)
        root = merge(merge(merge(merge(A, B2), C), B1), D);
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
    unsigned rng = next_seed();                 // ver next_seed(): semilla del reloj, no fija

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
        static unsigned seed = IMPLICIT_TREAP_SEED;
#else
        static unsigned seed =
            (unsigned)chrono::high_resolution_clock::now().time_since_epoch().count() | 1u;
#endif
        seed ^= seed << 13;                     // xorshift32 nunca sale de los no nulos,
        seed ^= seed >> 17;                     // asi que el | 1u alcanza para no quedar en 0
        seed ^= seed << 5;
        return seed;
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

    // Los nodos de las posiciones 0..n-1 ya estan en el pool, en base..base+hi y EN ORDEN,
    // asi que solo hay que enlazarlos balanceado. Eso no cumple la propiedad de heap, y medido
    // no importa: tras cualquier carga real la profundidad converge a la de un treap aleatorio,
    // y arrancar balanceado es mas chato que arrancar con el arbol cartesiano de las prioridades.
    int build(int base, int lo, int hi) {
        if(lo > hi) {
            return 0;
        }

        int mid = lo + (hi - lo) / 2;
        int t = base + mid;
        st[t].lc = build(base, lo, mid - 1);
        st[t].rc = build(base, mid + 1, hi);
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
        if constexpr (HAS_LAZY) {               // incondicional, como en LazySegmentTree
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

    void split(int t, int k, int& a, int& b) {  // los primeros k van a 'a'
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
    void prod(int t, int lo, int l, int r, LazyUpdate pend, bool rv, Node& acc, bool& has) const {
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
                piece.apply(pend, st[t].sz);
            }

            join(acc, has, piece);
            return;
        }

        LazyUpdate down = st[t].lz;

        if constexpr (HAS_LAZY) {
            down *= pend;                          // el lz del nodo primero, el carry despues
        }

        // rv es el flag ENTRANTE: dice si los hijos de t estan dados vuelta
        int fst = rv ? st[t].rc : st[t].lc;
        int snd = rv ? st[t].lc : st[t].rc;
        bool rv2 = rv != st[t].rev;             // esto baja
        int mid = lo + st[fst].sz;

        prod(fst, lo, l, r, down, rv2, acc, has);

        if(l <= mid && mid <= r) {
            Node own = st[t].val;

            if constexpr (HAS_LAZY) {
                own.apply(pend, 1);                // el propio usa pend, no down
            }

            join(acc, has, own);
        }

        prod(snd, mid + 1, l, r, down, rv2, acc, has);
    }

    // Menor p de [l, r] con pred(prod(l, p)) FALSA, o r + 1. acc/has entran valiendo
    // prod(l, lo - 1). Lleva lo pendiente en pend y en rv igual que prod: no escribe nada,
    // asi que un descenso no reestructura ni ensucia el arbol.
    template <class F>
    int corte_izq(int cur, int lo, int l, int r, LazyUpdate pend, bool rv,
                  Node& acc, bool& has, F pred) const {
        if(!cur) {
            return r + 1;
        }

        int hi = lo + st[cur].sz - 1;

        if(hi < l || r < lo) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if(l <= lo && hi <= r) {                // el subarbol entra completo en [l, r]
            Node piece = st[cur].agg;

            if(rv) {
                piece.reverse();
            }

            if constexpr (HAS_LAZY) {
                piece.apply(pend, st[cur].sz);
            }

            Node cand = has ? acc + piece : piece;   // acc a la izquierda, la pieza a la derecha

            if(pred(cand)) {
                acc = cand;
                has = true;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lo == hi) {
                return lo;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        LazyUpdate down = st[cur].lz;

        if constexpr (HAS_LAZY) {
            down *= pend;
        }

        int fst = rv ? st[cur].rc : st[cur].lc;
        int snd = rv ? st[cur].lc : st[cur].rc;
        bool rv2 = rv != st[cur].rev;
        int mid = lo + st[fst].sz;

        int res = corte_izq(fst, lo, l, r, down, rv2, acc, has, pred);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        if(l <= mid && mid <= r) {
            Node own = st[cur].val;

            if constexpr (HAS_LAZY) {
                own.apply(pend, 1);             // el propio usa pend, no down
            }

            Node cand = has ? acc + own : own;

            if(!pred(cand)) {
                return mid;
            }

            acc = cand;
            has = true;
        }

        return corte_izq(snd, mid + 1, l, r, down, rv2, acc, has, pred);
    }

    // Mayor p de [l, r] con pred(prod(p, r)) FALSA, o l - 1. acc/has entran valiendo
    // prod(hi + 1, r), asi que cada pieza se suma a la IZQUIERDA de acc. Recorre al reves.
    template <class F>
    int corte_der(int cur, int lo, int l, int r, LazyUpdate pend, bool rv,
                  Node& acc, bool& has, F pred) const {
        if(!cur) {
            return l - 1;
        }

        int hi = lo + st[cur].sz - 1;

        if(hi < l || r < lo) {
            return l - 1;
        }

        if(l <= lo && hi <= r) {
            Node piece = st[cur].agg;

            if(rv) {
                piece.reverse();
            }

            if constexpr (HAS_LAZY) {
                piece.apply(pend, st[cur].sz);
            }

            Node cand = has ? piece + acc : piece;   // la pieza a la IZQUIERDA de acc

            if(pred(cand)) {
                acc = cand;
                has = true;
                return l - 1;
            }

            if(lo == hi) {
                return lo;
            }
        }

        LazyUpdate down = st[cur].lz;

        if constexpr (HAS_LAZY) {
            down *= pend;
        }

        int fst = rv ? st[cur].rc : st[cur].lc;
        int snd = rv ? st[cur].lc : st[cur].rc;
        bool rv2 = rv != st[cur].rev;
        int mid = lo + st[fst].sz;

        int res = corte_der(snd, mid + 1, l, r, down, rv2, acc, has, pred);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        if(l <= mid && mid <= r) {
            Node own = st[cur].val;

            if constexpr (HAS_LAZY) {
                own.apply(pend, 1);
            }

            Node cand = has ? own + acc : own;

            if(!pred(cand)) {
                return mid;
            }

            acc = cand;
            has = true;
        }

        return corte_der(fst, lo, l, r, down, rv2, acc, has, pred);
    }

    // Recorre en orden simetrico los elementos de [l, r] y los apila. Como prod, lleva lo
    // pendiente en f y en rv y no escribe nada. No corta en los subarboles cubiertos porque
    // de todas formas hacen falta todos sus elementos.
    void collect(int t, int lo, int l, int r, LazyUpdate pend, bool rv, vector<Node>& out) const {
        if(!t) {
            return;
        }

        int hi = lo + st[t].sz - 1;

        if(hi < l || r < lo) {
            return;
        }

        LazyUpdate down = st[t].lz;

        if constexpr (HAS_LAZY) {
            down *= pend;
        }

        int fst = rv ? st[t].rc : st[t].lc;
        int snd = rv ? st[t].lc : st[t].rc;
        bool rv2 = rv != st[t].rev;
        int mid = lo + st[fst].sz;

        collect(fst, lo, l, r, down, rv2, out);

        if(l <= mid && mid <= r) {
            Node own = st[t].val;

            if constexpr (HAS_LAZY) {
                own.apply(pend, 1);                // el propio usa pend, no down
            }

            out.push_back(own);
        }

        collect(snd, mid + 1, l, r, down, rv2, out);
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

        push(t);                                // aca si hay que empujar: vamos a escribir
        int mid = lo + st[st[t].lc].sz;
        apply(st[t].lc, lo, l, r, f);

        if(l <= mid && mid <= r) {
            st[t].val.apply(f, 1);
        }

        apply(st[t].rc, mid + 1, l, r, f);
        pull(t);
    }
};
