bool isPerfectSquare(long double x) {
    if (x >= 0) {
        long long sr = sqrt(x);

        return (sr * sr == x);
    }
    return false;
}
