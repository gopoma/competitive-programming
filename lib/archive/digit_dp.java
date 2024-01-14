//* https://atcoder.jp/contests/abc336/tasks/abc336_e
//* E - Digit Sum Divisible
import java.io.*;
import java.util.*;

public class Main {
static long[][][][][] dp;
static long[][][][][] check;
static long cur = 0;

public static void main(String[] args) throws FileNotFoundException {
    // PrintWriter out = new PrintWriter(new FileOutputStream(new File(
    // "output.txt")));
    PrintWriter out = new PrintWriter(System.out);
    Scanner in = new Scanner(System.in);


    long n = 1;
    dp = new long[15][2][2][145][145];
    check = new long[15][2][2][145][145];
    for (int i = 0; i < n; i++) {

        long l = 1;
        long r = in.nextLong();
        String L = "" + l;
        String R = "" + r;
        while (L.length() < R.length()) {
            L = "0" + L;
        }
        long result = 0;
        for (int j = 1; j <= 144; j++) {

            cur = cur + 1;
            result += count(0, 0, 0, j, 0, j, L, R);
        }
        out.println(result);
    }
    out.close();
}

public static long count(int index, int larger, int smaller, int left,
int mod, int sum, String L, String R) {
    if (index == L.length()) {
        if (left == 0 && mod == 0) {
            return 1;
        }
        return 0;
    }
    if((L.length() - index) * 9 < left){
        return 0;
    }
    if (check[index][larger][smaller][left][mod] == cur) {
        return dp[index][larger][smaller][left][mod];
    }
    //System.out.println(cur);
    check[index][larger][smaller][left][mod] = cur;
    int x = L.charAt(index) - '0';
    int y = R.charAt(index) - '0';
    long result = 0;
    for (int i = 0; i < 10 && i <= left; i++) {

        if (x > i && larger == 0) {
            continue;
        }
        if (y < i && smaller == 0) {
            continue;
        }
        int nxtLarger = larger;
        int nxtSmaller = smaller;
        if (x < i) {
            nxtLarger = 1;
        }
        if (y > i) {
            nxtSmaller = 1;
        }
        int nxtMod = (mod * 10 + i) % sum;
        result += count(index + 1, nxtLarger, nxtSmaller, left - i, nxtMod,
                sum, L, R);
    }
    return dp[index][larger][smaller][left][mod] = result;
}
}
