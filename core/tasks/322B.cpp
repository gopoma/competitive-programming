// Credits to Stanford ICPC
// Two-phase simplex algorithm for solving linear programs of the form
//
//     maximize     c^T x
//     subject to   Ax <= b
//                  x >= 0
//
// INPUT: A -- an m x n matrix
//        b -- an m-dimensional vector
//        c -- an n-dimensional vector
//        x -- a vector where the optimal solution will be stored
//
// OUTPUT: value of the optimal solution (infinity if unbounded
//         above, nan if infeasible)
//
// To use this code, create an LPSolver object with A, b, and c as
// arguments.  Then, call Solve(x).

#include <bits/stdc++.h>

using namespace std;

// for debugging!
#define MACRO(code) \
    do              \
    {               \
        code        \
    } while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x, y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x, y, z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x, y, z, w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";

    for (int i = 0; i < int(v.size()); i++)
    {
        if (i > 0)
            os << " ";
        os << v[i];
    }
    return os << "]";
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &v)
{
    vector<T> tmp;
    for (auto &e : v)
    {
        tmp.emplace_back(e);
    }

    return os << tmp;
}

template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &v)
{
    return os << "{" << v.first << ", " << v.second << "}";
}

typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;

struct LPSolver
{
    int m, n;
    VI B, N;
    VVD D;

    LPSolver(const VVD &A, const VD &b, const VD &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2))
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                D[i][j] = A[i][j];
        for (int i = 0; i < m; i++)
        {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++)
        {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void Pivot(int r, int s)
    {
        double inv = 1.0 / D[r][s];
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                for (int j = 0; j < n + 2; j++)
                    if (j != s)
                        D[i][j] -= D[r][j] * D[i][s] * inv;
        for (int j = 0; j < n + 2; j++)
            if (j != s)
                D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool Simplex(int phase)
    {
        int x = phase == 1 ? m + 1 : m;
        while (true)
        {
            int s = -1;
            for (int j = 0; j <= n; j++)
            {
                if (phase == 2 && N[j] == -1)
                    continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s])
                    s = j;
            }
            if (D[x][s] > -EPS)
                return true;
            int r = -1;
            for (int i = 0; i < m; i++)
            {
                if (D[i][s] < EPS)
                    continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                    (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r])
                    r = i;
            }
            if (r == -1)
                return false;
            Pivot(r, s);
        }
    }

    DOUBLE Solve(VD &x)
    {
        int r = 0;
        for (int i = 1; i < m; i++)
            if (D[i][n + 1] < D[r][n + 1])
                r = i;
        if (D[r][n + 1] < -EPS)
        {
            Pivot(r, n);
            if (!Simplex(1) || D[m + 1][n + 1] < -EPS)
                return -numeric_limits<DOUBLE>::infinity();
            for (int i = 0; i < m; i++)
                if (B[i] == -1)
                {
                    int s = -1;
                    for (int j = 0; j <= n; j++)
                        if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s])
                            s = j;
                    Pivot(i, s);
                }
        }
        if (!Simplex(2))
            return numeric_limits<DOUBLE>::infinity();
        x = VD(n);
        for (int i = 0; i < m; i++)
            if (B[i] < n)
                x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};

bool is_unimodular(VVD &A)
{
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = i + 1; j < A.size(); ++j)
        {
            for (int k = 0; k < A[0].size(); ++k)
            {
                for (int l = k + 1; l < A[0].size(); ++l)
                {
                    int det = A[i][k] * A[j][l] - A[i][l] * A[j][k];
                    if (det != 0 and det != 1 and det != -1)
                        return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    VVD A{
        {3, 0, 0, 1},
        {0, 3, 0, 1},
        {0, 0, 3, 1},
    };
    assert(is_unimodular(A));
    VD b(3, 0);
    VD c(4, 1);

    DBG(is_unimodular(A));

    //!
    cin >> b[0] >> b[1] >> b[2];

    for (int i = 0; i < int(c.size()); i++)
        c[i] *= -1;
    DBG2(b, c);

    //!

    LPSolver solver(A, b, c);
    VD x;

    long long value = (long long)(solver.Solve(x) * -1);

    DBG2(value, x);
    // cout << value << endl;
}
