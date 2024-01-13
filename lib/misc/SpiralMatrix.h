#include <bits/stdc++.h>
//? Description: Function to form the spiral matrix
//? Source: shttps://www.geeksforgeeks.org/form-a-spiral-matrix-from-the-given-array/
//? Verification: https://atcoder.jp/contests/abc335/tasks/abc335_d

//? Input
//* 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

//? Output
//* 1 2 3 4 5
//* 16 17 18 19 6
//* 15 24 25 20 7
//* 14 23 22 21 8
//* 13 12 11 10 9

//? API:
//* vi go(N * N);
//* for(int i = 0; i < N * N; i++) go[i] = i + 1;
//* vector<vector<int>> res = formSpiralMatrix(go, N, N);

//?
vector<vector<int>> formSpiralMatrix(vi arr, int R, int C) {
    vector<vector<int>> mat(R, vector<int>(C));

    int top = 0,
        bottom = R - 1,
        left = 0,
        right = C - 1;

    int index = 0;

    while (1) {

        if (left > right)
            break;

        // print top row
        for (int i = left; i <= right; i++)
            mat[top][i] = arr[index++];
        top++;

        if (top > bottom)
            break;

        // print right column
        for (int i = top; i <= bottom; i++)
            mat[i][right] = arr[index++];
        right--;

        if (left > right)
            break;

        // print bottom row
        for (int i = right; i >= left; i--)
            mat[bottom][i] = arr[index++];
        bottom--;

        if (top > bottom)
            break;

        // print left column
        for (int i = bottom; i >= top; i--)
            mat[i][left] = arr[index++];
        left++;
    }

    return mat;
}
