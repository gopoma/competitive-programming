long long mex(vector<long long> const& A) {
    set<long long> b(A.begin(), A.end());

    long long result = 0;
    while (b.count(result))
        ++result;
    return result;
}
