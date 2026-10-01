/**
 * Description: Persistent segment tree with index implementation.
 * Time: O(log N) per point set and inclusive range query, O(N) build.
 * Memory: O(number_of_versions * log N) nodes after build/init.
 * Source:
 *  - https://usaco.guide/adv/persistent
 *
 * Notes:
 *  - This is the general version. Values are joined with operator+.
 *  - Use a custom node type with a default constructor and operator+,
 *    as in SegmentTree.h.
 *  - Version 0 is the initial tree: all ID after init(n), or the array after build(a).
 *  - Internal node storage grows with push_back; no precomputed reserve is required.
 *  - All public range methods use zero-indexed inclusive ranges [l, r].
 *
 * API:
 *  PersistentSegmentTree<node> pst;
 *  pst.init(n);                         // root(0) is all ID
 *  int r1 = pst.set(pst.root(0), i, x); // creates version 1 from version 0
 *  node ans = pst.prod(r1, l, r);       // inclusive [l, r]
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

template <class T>
struct PersistentSegmentTree {
  public:
    PersistentSegmentTree() { reset_null(); }

    explicit PersistentSegmentTree(int _n, T _ID = T{}) : ID(_ID) {
        init(_n);
    }

    explicit PersistentSegmentTree(const vector<T>& a, T _ID = T{}) : ID(_ID) {
        build(a);
    }

    void init(int _n) {
        assert(_n >= 1);
        n = _n;
        reset_null();
        roots.push_back(0);
    }

    void build(const vector<T>& a) {
        init(max(1, int(a.size())));
        roots[0] = build(0, n - 1, a);
    }

    int version_count() const {
        return int(roots.size());
    }

    int get_time() const {
        return version_count() - 1;
    }

    int root(int version) const {
        assert(valid_version(version));
        return roots[version];
    }

    int latest_root() const {
        assert(!roots.empty());
        return roots.back();
    }

    int copy_root(int rt) {
        assert(valid_root(rt));
        roots.push_back(rt);
        return rt;
    }

    int copy_version(int version) {
        assert(valid_version(version));
        return copy_root(roots[version]);
    }

    int set(int rt, int pos, T value) {
        assert(valid_root(rt));
        assert(0 <= pos && pos < n);
        int nr = set(rt, 0, n - 1, pos, value);
        roots.push_back(nr);
        return nr;
    }

    int set_version(int version, int pos, T value) {
        assert(valid_version(version));
        return set(roots[version], pos, value);
    }

    int set(int pos, T value) {
        return set(latest_root(), pos, value);
    }

    T get(int rt, int pos) const {
        assert(valid_root(rt));
        assert(0 <= pos && pos < n);
        return get(rt, 0, n - 1, pos);
    }

    T get_version(int version, int pos) const {
        assert(valid_version(version));
        return get(roots[version], pos);
    }

    T get(int pos) const {
        return get(latest_root(), pos);
    }

    T prod(int rt, int l, int r) const {
        assert(valid_root(rt));
        assert(0 <= l && l <= r && r < n);
        return prod(rt, 0, n - 1, l, r);
    }

    T prod_version(int version, int l, int r) const {
        assert(valid_version(version));
        return prod(roots[version], l, r);
    }

    T prod(int l, int r) const {
        return prod(latest_root(), l, r);
    }

    T all_prod(int rt) const {
        assert(valid_root(rt));
        return st[rt].val;
    }

    T all_prod_version(int version) const {
        assert(valid_version(version));
        return all_prod(roots[version]);
    }

    T all_prod() const {
        return all_prod(latest_root());
    }

  private:
    struct InternalNode {
        int l = 0;
        int r = 0;
        T val{};
    };

    int n = 0;
    T ID{};
    vector<InternalNode> st;
    vector<int> roots;

    T cmb(const T& a, const T& b) const {
        return a + b;
    }

    int new_node(const InternalNode& node = InternalNode()) {
        st.push_back(node);
        return int(st.size()) - 1;
    }

    int clone_node(int node) {
        return new_node(st[node]);
    }

    void reset_null() {
        st.assign(1, InternalNode{0, 0, ID});
        roots.clear();
    }

    bool valid_root(int rt) const {
        return 0 <= rt && rt < int(st.size());
    }

    bool valid_version(int version) const {
        return 0 <= version && version < int(roots.size());
    }

    int build(int lx, int rx, const vector<T>& a) {
        int cur = new_node();
        if(lx == rx) {
            st[cur].val = (lx < int(a.size()) ? a[lx] : ID);
            return cur;
        }

        int mx = (lx + rx) / 2;
        st[cur].l = build(lx, mx, a);
        st[cur].r = build(mx + 1, rx, a);
        pull(cur);
        return cur;
    }

    void pull(int cur) {
        st[cur].val = cmb(st[st[cur].l].val, st[st[cur].r].val);
    }

    int set(int cur, int lx, int rx, int pos, T value) {
        cur = clone_node(cur);
        if(lx == rx) {
            st[cur].val = value;
            return cur;
        }

        int mx = (lx + rx) / 2;
        if(pos <= mx) st[cur].l = set(st[cur].l, lx, mx, pos, value);
        else st[cur].r = set(st[cur].r, mx + 1, rx, pos, value);
        pull(cur);
        return cur;
    }

    T get(int cur, int lx, int rx, int pos) const {
        if(cur == 0) return ID;
        while(lx != rx) {
            int mx = (lx + rx) / 2;
            if(pos <= mx) {
                cur = st[cur].l;
                rx = mx;
            } else {
                cur = st[cur].r;
                lx = mx + 1;
            }
            if(cur == 0) return ID;
        }
        return st[cur].val;
    }

    T prod(int cur, int lx, int rx, int ql, int qr) const {
        if(cur == 0 || rx < ql || qr < lx) return ID;
        if(ql <= lx && rx <= qr) return st[cur].val;

        int mx = (lx + rx) / 2;
        return cmb(
            prod(st[cur].l, lx, mx, ql, qr),
            prod(st[cur].r, mx + 1, rx, ql, qr)
        );
    }
};
