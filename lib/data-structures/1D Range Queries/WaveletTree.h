template<typename T, typename C>
class bit_vector {
    static_assert(is_unsigned_v<T>);
    static constexpr int sT = sizeof(T) * 8;
    static constexpr int lgsT = __lg(sT);

    vector<pair<T, C>> m;

    __attribute__((always_inline))
    T allbits(int k) {
        return k == sT ? numeric_limits<T>::max() : (T(1) << k) - 1;
    }

    int popcount(T x) {
        if constexpr(sT <= 32) return __builtin_popcount(x);
        return __builtin_popcountll(x);
    }

public:
    bit_vector() = default;
    bit_vector(int n): m((n + sT - 1) >> lgsT, {0, 0}) {}

    void set(int i) {m[i >> lgsT].first |= T(1) << (i & (sT - 1));}
    int get(int i) {return m[i >> lgsT].first >> (i & (sT - 1)) & 1;}

    void prepare() {
        for (size_t i = 1; i < m.size(); ++i) m[i].second = m[i - 1].second + popcount(m[i - 1].first);
    }

    C pref1(int k) {
        auto [a, b] = m[k >> lgsT];
        return b + popcount(a & allbits((k & (sT - 1)) + 1));
    }

    C pref0(int k) {return k + 1 - pref1(k);}
    C seg0(int l, int r) {return pref0(r) - (l ? pref0(l - 1) : 0);}
    C seg1(int l, int r) {return pref1(r) - (l ? pref1(l - 1) : 0);}
};


template<typename T, typename C, bool do_compress, bool use_sum>
class wavelet_tree {
    static_assert(is_integral_v<T>);
    size_t n, lg;
    vector<T> keys;
    T mne, mxe;
    using bitvec = bit_vector<uint32_t, uint32_t>;
    vector<bitvec> bvs;
    vector<vector<C>> sums;

    C get_sum(size_t layer, size_t l, size_t r) {
        // cout << layer << ' ' << r << " " << sums[layer].size() << endl;
        assert(layer < sums.size());
        assert(l <= r);
        assert(r < sums[layer].size());
        return sums[layer][r] - (l ? sums[layer][l - 1] : 0);
    }

public:
    wavelet_tree() = default;
    //O(nlog(n)) time and O(n) memory for preparation
    template<typename I>
    wavelet_tree(I first, I last, vector<T> sum_data = {}): n(std::distance(first, last)) {
        if (!n) return;
        vector<T> m(first, last);
        vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
        if (do_compress) {
            sort(idx.begin(), idx.end(), [&m](int l, int r) {return m[l] < m[r];});
            keys.reserve(n);
            for (int i : idx) {
                if (keys.empty() || keys.back() != m[i]) keys.emplace_back(m[i]);
                m[i] = keys.size() - 1;
            }
            keys.shrink_to_fit();
        }
        const auto [mni, mxi] = minmax_element(m.begin(), m.end());
        mne = *mni, mxe = *mxi;
        size_t D = mxe - mne + 1;
        lg = __lg(D) + (D & (D - 1) ? 2 : 1);
        bvs.resize(lg, bitvec(n));
        if constexpr (use_sum) sums.resize(lg, vector<C>(n));
        if (do_compress) iota(idx.begin(), idx.end(), 0);
        function<void(int, int, int, T, T)> build = [&](int layer, int l, int r, T vl, T vr) {
            if (l > r || vl == vr) return;
            T vm = vl + (vr - vl) / 2;
            for (int i = l; i <= r; ++i) {
                if (m[idx[i]] > vm) {
                    bvs[layer].set(i);
                } else if constexpr (use_sum) {
                    sums[layer][i] = sum_data[idx[i]];
                }
            }
            int p = stable_partition(idx.begin() + l, idx.begin() + r + 1, [&](int x) {return m[x] <= vm;}) - idx.begin();
            build(layer + 1, l, p - 1, vl, vm);
            build(layer + 1, p, r, vm + 1, vr);
        };
        build(0, 0, n - 1, mne, mxe);
        for (auto& bv : bvs) bv.prepare();
        for (auto& row : sums) partial_sum(row.begin(), row.end(), row.begin());
    }

    //O(log(# distinct)) if do_compress == true, O(log(mxe - mne)) otherwise
    T seg_kth_ordered_statistics(int ql, int qr, int k) {
        assert(ql <= qr && qr < n);
        assert(k <= qr - ql);
        int l = 0, r = n - 1;
        T vl = mne, vr = mxe;
        for (int layer = 0; vl < vr; ++layer) {
            T vm = vl + (vr - vl) / 2;
            int c0 = bvs[layer].seg0(l, r);
            int cq0 = bvs[layer].seg0(ql, qr);
            int cq1 = qr - ql + 1 - cq0;
            if (k < cq0) {
                ql = l + (ql ? bvs[layer].seg0(l, ql - 1) : 0);
                qr = ql + cq0 - 1;
                r = l + c0 - 1;
                vr = vm;
            } else {
                k -= cq0;
                ql = l + c0 + (ql ? bvs[layer].seg1(l, ql - 1) : 0);
                qr = ql + cq1 - 1;
                l = l + c0;
                vl = vm + 1;
            }
        }
        return do_compress ? keys[vl] : vl;
    }

    //O(log(# distinct)) if do_compress == true, O(log(mxe - mne)) otherwise
    pair<int, C> seg_count_leq(int ql, int qr, T x) {
        assert(ql <= qr && qr < n);
        if (do_compress) {
            auto it = upper_bound(keys.begin(), keys.end(), x);
            if (it == keys.begin()) return {0, 0};
            x = it - keys.begin() - 1;
        }
        int l = 0, r = n - 1;
        T vl = mne, vr = mxe;
        int res = 0;
        C res_sum = 0;
        for (int layer = 0; vl < vr && ql <= qr; ++layer) {
            T vm = vl + (vr - vl) / 2;
            int c0 = bvs[layer].seg0(l, r);
            int cq0 = bvs[layer].seg0(ql, qr);
            int cq1 = qr - ql + 1 - cq0;
            if (x <= vm) {
                ql = l + (ql ? bvs[layer].seg0(l, ql - 1) : 0);
                qr = ql + cq0 - 1;
                r = l + c0 - 1;
                vr = vm;
            } else {
                res += cq0;
                if constexpr (use_sum) res_sum += get_sum(layer, ql, qr);
                ql = l + c0 + (ql ? bvs[layer].seg1(l, ql - 1) : 0);
                qr = ql + cq1 - 1;
                l = l + c0;
                vl = vm + 1;
            }
        }
        if (vl == vr && vl <= x && ql <= qr) {
            res += qr - ql + 1;
            res_sum += C(do_compress ? keys[vl] : vl) * (qr - ql + 1);
        }
        return {res, res_sum};
    }

    //O(log(# distinct)) if do_compress == true, O(log(mxe - mne)) otherwise
    int seg_count_seg(int ql, int qr, T x, T y) {
        assert(ql <= qr && qr < n);
        if (x > y) return 0;
        if (do_compress) {
            auto ix = lower_bound(keys.begin(), keys.end(), x);
            if (ix == keys.begin()) return seg_count_leq(ql, qr, y);
            x = ix - keys.begin();
            auto iy = upper_bound(keys.begin(), keys.end(), y);
            y = iy - keys.begin() - 1;
        }
        int res = 0;
        auto dfs = [&](auto&& dfs, int layer, int l, int r, int ql, int qr, T vl, T vr) {
            if (vr < x || y < vl || ql > qr || l > r) return;
            if (x <= vl && vr <= y) {
                res += qr - ql + 1;
                return;
            }
            T vm = vl + (vr - vl) / 2;
            int c0 = bvs[layer].seg0(l, r);
            int cq0 = bvs[layer].seg0(ql, qr);
            int cq1 = qr - ql + 1 - cq0;
            int lfql = l + (ql ? bvs[layer].seg0(l, ql - 1) : 0), lfqr = lfql + cq0 - 1;
            dfs(dfs, layer + 1, l, l + c0 - 1, lfql, lfqr, vl, vm);
            int rgql = l + c0 + (ql ? bvs[layer].seg1(l, ql - 1) : 0), rgqr = rgql + cq1 - 1;
            dfs(dfs, layer + 1, l + c0, r, rgql, rgqr, vm + 1, vr);
        };
        dfs(dfs, 0, 0, n - 1, ql, qr, mne, mxe);
        return res;
    }
};
