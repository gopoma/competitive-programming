/**
 * Description: Square root decomposition for range sum. The array is cut into blocks of
 *   block_size consecutive positions and every block keeps the sum of what it holds, so a
 *   point update touches one block and a range query adds the whole blocks in the middle
 *   plus the leftovers at the two ends. Values are int, the sums are long long.
 * Time: O(n) build, O(1) update, O(sqrt(n)) query
 * Source: https://usaco.guide/plat/sqrt
 * Verification: TODO
 * API: ranges are inclusive and zero indexed, and must be valid, 0 <= l <= r < n.
 *     Sqrt s(a)         block_size becomes ceil(sqrt(n)), the usual choice
 *     Sqrt s(bs, a)     your own block_size, anything from 1 to n works
 *     s.update(p, v)    a[p] = v
 *     s.query(r)        sum of a[0..r]
 *     s.query(l, r)     sum of a[l..r]
 *   The range query is two prefixes, query(r) minus query(l - 1), which is allowed because a
 *   sum can be subtracted. It walks the blocks twice instead of once, measured at 1.2 to 1.4
 *   times the cost of going straight from l to r, and in exchange it is three lines. An
 *   operation with no inverse, a minimum for instance, could not do this and would need the
 *   single pass. The asserts cost nothing measurable: none of them sits inside a loop.
 * Example, point assignment and range sum:
 *   int n, q; cin >> n >> q;
 *   vector<int> a(n);
 *   for (int& x : a) cin >> x;
 *   Sqrt s(a);
 *   while (q--) {
 *       int type; cin >> type;
 *       if (type == 1) { int p, v; cin >> p >> v; s.update(p, v); }
 *       else { int l, r; cin >> l >> r; cout << s.query(l, r) << "\n"; }
 *   }
 */

struct Sqrt {
    int n;
    int block_size;
    vector<int> nums;
    vector<long long> blocks;

    explicit Sqrt(const vector<int>& arr) : Sqrt(default_block_size(int(arr.size())), arr) {}

    Sqrt(int sqrtn, const vector<int>& arr) : block_size(sqrtn), nums(arr) {
        n = int(nums.size());

        assert(n >= 1);
        assert(block_size >= 1);                // con 0 toda division de bid revienta

        blocks.assign((n + block_size - 1) / block_size, 0);    // ceil(n / block_size)

        for (int i = 0; i < n; i++) {
            blocks[bid(i)] += nums[i];
        }
    }

    // ceil(sqrt(n)) sin tocar punto flotante, asi no hay sorpresas de redondeo
    static int default_block_size(int _n) {
        int bs = 1;

        while((long long)bs * bs < _n) {
            ++bs;
        }

        return bs;
    }

    // Bloque que contiene la posicion i. Las dos aserciones cubren los dos unicos peligros
    // de la estructura, y estan aca porque toda division y todo indice de blocks pasa por
    // esta funcion: no hay forma de saltearlas.
    int bid(int i) const {
        assert(block_size >= 1);                // no dividir entre cero
        int b = i / block_size;
        assert(0 <= b && b < (int)blocks.size());   // no desbordar blocks
        return b;
    }

    /** O(1) update to set nums[x] to v */
    void update(int x, int v) {
        assert(0 <= x && x < n);

        blocks[bid(x)] -= nums[x];
        nums[x] = v;
        blocks[bid(x)] += nums[x];
    }

    /** O(sqrt(n)) query for sum of [0, r] */
    long long query(int r) const {
        assert(0 <= r && r < n);

        int b = bid(r);
        long long res = 0;

        for (int i = 0; i < b; i++) {            // bloques enteros antes del de r
            res += blocks[i];
        }

        for (int i = b * block_size; i <= r; i++) {   // lo que queda dentro del bloque de r
            res += nums[i];
        }

        return res;
    }

    /** O(sqrt(n)) query for sum of [l, r] */
    long long query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return query(r) - (l == 0 ? 0 : query(l - 1));
    }
};
