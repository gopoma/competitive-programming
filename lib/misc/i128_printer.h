// i128 X = i128(a[1]) * i128(a[n - 1]);
// cout << X << " " << X << "\n";

using i128 = __int128;
std::ostream& operator<<(std::ostream& o, const __int128& x) {
    if (x == std::numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << (x / i128(10)) << (char)(x % 10 + '0');
}
