struct Interval {
    int l;
    int r;
    int idx;

    Interval() {}

    Interval(int _l, int _r, int _idx): l(_l), r(_r), idx(_idx) {}

    bool operator<(const Interval& rhs) {
        if(l == rhs.l) return r > rhs.r;
        return l < rhs.l;
    }
};

vector<Interval> sgmts(n);
for(int i = 0; i < n; i++) {
    int l, r; cin >> l >> r;

    sgmts[i] = Interval(l, r, i);
}

sor(sgmts); // TODO: For Sorting!

each(x, sgmts) dbg(x.l, x.r, x.idx);
