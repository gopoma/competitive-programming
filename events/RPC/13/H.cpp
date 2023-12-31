#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct calendar
{
    int day;
    int month;
    int year;
};
int main()
{
	cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams

    long long n;
    cin >> n;
    ll a[n];
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    calendar b[2];
    for (long long i = 0; i < 2; i++)
    {
        cin >> b[i].day;
        cin >> b[i].month;
        cin >> b[i].year;
    }
    vector<long long> pref(n, 0);
    pref[0] = a[0];
    for (long long i = 1; i < n; i++)
    {
        pref[i] = pref[i - 1] + a[i];
    }
    vector<long long> acc(2, 0);
    for (long long i = 0; i < 2; i++)
    {

        acc[i] += (b[i].year - 1) * pref[n - 1];
        acc[i] += (b[i].month - 2 >= 0 ? pref[b[i].month - 2] : 0ll);
        acc[i] += b[i].day;
    }
    long long ans = abs(acc[0] - acc[1]);
    cout << ans << "\n";
    return 0;
}
