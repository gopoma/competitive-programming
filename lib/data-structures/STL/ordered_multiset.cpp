//* Template
/**
 * Description: A set (not multiset!) with support for finding the $n$'th
   * element, and finding the index of an element. Change \texttt{null\_type} to get a map.
 * Time: O(\log N)
 * Source: KACTL
   * https://codeforces.com/blog/entry/11080
 * Verification: many
 */
#undef _GLIBCXX_DEBUG //* for Stress Testing
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// typedef tree<int, null_type, greater_equal<int>, rb_tree_tag,
//              tree_order_statistics_node_update> ordered_multiset;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
              tree_order_statistics_node_update> ordered_multiset;
#define ook order_of_key
#define fbo find_by_order
//* /Template



void solve() {
    ordered_multiset st; // less_equal<int>
    dbg(st);

    st.ins(1);
    st.ins(2);
    st.ins(2);
    st.ins(3);
    st.ins(3);
    st.ins(3);
    dbg(st);

    dbg(*st.fbo(0));
    dbg(*st.fbo(1));
    dbg(*st.fbo(2));
    dbg(*st.fbo(3));
    dbg(*st.fbo(4));
    dbg(*st.fbo(5));

    dbg(st.ook(1));
    dbg(st.ook(2));
    dbg(st.ook(3));

    // st = []
    // st = [1, 2, 2, 3, 3, 3]
    // *st.fbo(0) = 1
    // *st.fbo(1) = 2
    // *st.fbo(2) = 2
    // *st.fbo(3) = 3
    // *st.fbo(4) = 3
    // *st.fbo(5) = 3
    // st.ook(1) = 0
    // st.ook(2) = 1
    // st.ook(3) = 3
}
