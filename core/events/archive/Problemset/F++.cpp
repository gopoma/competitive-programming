#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define F first
#define S second
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

class SegmentTree {
    vector<ll> seg; // Segment Tree to be stored in a vector.
public:
    SegmentTree() {}
    SegmentTree(vector<ll>& nums) {
        int n = nums.size();
        seg.resize(4 * n, 0);  // Maximum size of a segment tree for an array of size n is 4n
        buildTree(nums, 0, 0, n - 1); // Build the segment tree
    }
    void buildTree(vector<ll>& nums, int pos, int left, int right) {
        if (left == right) {
            seg[pos] = nums[left];
            return;
        }
        int mid = left + (right - left) / 2;
        buildTree(nums, 2 * pos + 1, left, mid);
        buildTree(nums, 2 * pos + 2, mid + 1, right);
        seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
    }
    void updateTree(int pos, int left, int right, int idx, ll val) {
        // no overlap
        if (idx < left || idx > right) return;

        // total overlap
        if (left == right) {
            if (left == idx) seg[pos] = val;
            return;
        }
        // partial overlap
        int mid = left + (right - left) / 2;
        updateTree(2 * pos + 1, left, mid, idx, val);
        updateTree(2 * pos + 2, mid + 1, right, idx, val);
        seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
    }

    ll queryTree(int qleft, int qright, int left, int right, int pos) {
        if (qleft <= left && qright >= right) { // total overlap
            return seg[pos];
        }
        if (qleft > right || qright < left)  {  // no overlap
            return 0;
        }
        // partial overlap
        int mid = left + (right - left) / 2;
        return queryTree(qleft, qright, left, mid, 2 * pos + 1) + queryTree(qleft, qright, mid + 1, right, 2 * pos + 2);
    }
};

class NumArray {
    SegmentTree st;
    int n;  // Length of the num vector.
public:
    NumArray(vector<ll>& nums) {
        this->st = SegmentTree(nums);
        this->n = nums.size();
    }

    void update(int index, ll val) {
        st.updateTree(0, 0, n - 1, index, val);
    }

    ll sumRange(int left, int right) {
        return st.queryTree(left, right, 0, n - 1, 0);
    }
};

/*
class NumArray {
public:
    vector<ll> seg;
    int n;

    void buildTree(vector<ll>& nums, int pos, int left, int right){
        if (left == right){
            seg[pos] = nums[left];
            return;
        }

        int mid = (left+right)/2;
        buildTree(nums, 2*pos+1, left, mid);
        buildTree(nums, 2*pos+2, mid+1, right);
        seg[pos] = seg[2*pos+1]+seg[2*pos+2];
    }

    void updateUtil(int pos, int left, int right, int index, ll val) {
        if(index <left || index >right) return;

        if(left==right){
            if(left==index)
                seg[pos]=val;
            return;
        }

        int mid=(left+right)/2;
        updateUtil(2*pos+1,left,mid,index,val);
        updateUtil(2*pos+2,mid+1,right,index,val);
        seg[pos]=seg[2*pos+1]+seg[2*pos+2];
    }

    ll rangeUtil(int qlow, int qhigh, int low, int high, int pos){
        if (qlow <= low && qhigh>= high) {
            return seg[pos];
        }
        if (qlow > high || qhigh < low) {
            return 0;
        }

        int mid = low+(high-low)/2;
        return (rangeUtil(qlow, qhigh, low, mid, 2*pos+1) + rangeUtil(qlow, qhigh, mid+1, high, 2*pos+2));
    }

    NumArray(vector<ll>& nums) {
        if(nums.size() > 0){
            n = nums.size();
            seg.resize(4*n,0);
            buildTree(nums, 0, 0, n-1);
        }
    }

    void update(int index, ll val) {
        if(n==0)return;
        updateUtil(0,0,n-1, index, val);
    }

    ll sumRange(int left, int right) {
        if(n==0)return 0;
        return rangeUtil(left, right, 0, n-1, 0);
    }
};
*/



void solve() {
    int n;
    cin >> n;

    vector<ll> A(n+1, 0);
    for(int i = 1; i <= n; i++)
        cin >> A[i];

    NumArray* tree = new NumArray(A);

    int q;
    cin >> q;

    while(q--) {
        char tipo;
        cin >> tipo;
        assert(tipo == 'R' || tipo == 'U');

        if(tipo == 'R') {
            int left, right;
            cin >> left >> right;

            cout << tree->sumRange(left, right) << nl;
        } else {
            ll pos, surplus;
            cin >> pos >> surplus;

            A[pos] += surplus;
            tree->update(pos, A[pos]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
