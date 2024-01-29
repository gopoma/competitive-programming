// function to calculate Small
// result between two arrays
ll findSmallestDifference(vl& A, vl& B) {
    const int m = sz(A);
    const int n = sz(B);

    int a = 0, b = 0;

    // Initialize result as max value
    ll result = BIG;

    // Scan Both Arrays upto
    // sizeof of the Arrays
    while (a < m && b < n) {
        if (abs(A[a] - B[b]) < result)
            result = abs(A[a] - B[b]);

        // Move Smaller Value
        if (A[a] < B[b])
            a++;

        else
            b++;
    }

    // return final sma result
    return result;
}
