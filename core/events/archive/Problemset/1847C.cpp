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

#define INT_SIZE 32

struct TrieNode {
    int value;
    TrieNode *arr[2];
};

TrieNode *newNode() {
    TrieNode *temp = new TrieNode;
    temp->value = 0;
    temp->arr[0] = temp->arr[1] = NULL;
    return temp;
}

void insert(TrieNode *root, int pre_xor) {
    TrieNode *temp = root;

    for (int i=INT_SIZE-1; i>=0; i--) {
        bool val = pre_xor & (1<<i);

        if (temp->arr[val] == NULL)
            temp->arr[val] = newNode();

        temp = temp->arr[val];
    }

    temp->value = pre_xor;
}

int query(TrieNode *root, int pre_xor) {
    TrieNode *temp = root;
    for (int i=INT_SIZE-1; i>=0; i--) {
        bool val = pre_xor & (1<<i);

        if (temp->arr[1-val]!=NULL)
            temp = temp->arr[1-val];

        else if (temp->arr[val] != NULL)
            temp = temp->arr[val];
    }
    return pre_xor^(temp->value);
}

int maxSubarrayXOR(int arr[], int n) {
    TrieNode *root = newNode();
    insert(root, 0);

    int result = INT_MIN, pre_xor =0;

    for (int i=0; i<n; i++) {
        pre_xor = pre_xor^arr[i];
        insert(root, pre_xor);

        result = max(result, query(root, pre_xor));
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        int A[n];
        for(auto& a: A) cin >> a;
        cout << maxSubarrayXOR(A, n) << "\n";
    }

    return 0;
}
