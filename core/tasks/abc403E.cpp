#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m" << endl;)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
//* /Debugger

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

//* Template
/**
 * Description: insert string of lowercase letters
 */

using str = string;

 struct vertex {
    char alphabet;
    bool isEnd;
    int cnt;
    //? vector<vertex *> child;
    map<int, vertex *> child;

    vertex(char a) : alphabet(a), cnt(0), isEnd(false) {
        //? child.assign(26, NULL);
    }
};

class Trie {        // this is TRIE
private:            // NOT Suffix Trie
    vertex *root;

public:
    Trie() { root = new vertex('!'); }

    void insert(string word) { // insert a word into trie
        vertex *cur = root;
        for (int i = 0; i < (int)word.size(); ++i) { // O(n)
            cur->cnt++;
            int alphaNum = word[i] - 'a';
            if (cur->child[alphaNum] == NULL) // add new branch if NULL
                cur->child[alphaNum] = new vertex(word[i]);
            cur = cur->child[alphaNum];
        }
        assert(cur->alphabet == word.back());
        dbg("adi", word);
        cur->cnt++;
        cur->isEnd = true;
    }

    bool checkTerminal(string word) { // true if match prefix
        vertex *cur = root;
        for (int i = 0; i < (int)word.size(); ++i) {
            int alphaNum = word[i] - 'a';
            if(cur->isEnd)
                return true;
            if (cur->child[alphaNum] == NULL) // not found
                return false;
            cur = cur->child[alphaNum];
        }
        return (cur->isEnd);
    }

    void balance(string word) {
        dbg("balance", word);
        vertex *cur = root;
        for (int i = 0; i < (int)word.size() - 1; ++i) {
            int alphaNum = word[i] - 'a';
            if (cur->child[alphaNum] == NULL) { // not found
                dbg("nothing to balance 1");
                return;
            }
            cur = cur->child[alphaNum];
        }

        if(cur->child[word.back() - 'a'] == NULL) {
            dbg("nothing to balance 2");
            return;
        }

        dbg("balancing!");

        int ret = cur->child[word.back() - 'a']->cnt;
        dbg(ret);

        cur = root;
        for (int i = 0; i < (int)word.size() - 1; ++i) {
            int alphaNum = word[i] - 'a';
            cur->cnt -= ret;
            cur = cur->child[alphaNum];
        }

        cur->cnt -= ret;
        assert(cur->child[word.back() - 'a'] != NULL);
        cur->child[word.back() - 'a'] = NULL;
    }

    int query() {
        return root->cnt;
    }

    bool startsWith(string prefix) { // true if match prefix
        vertex *cur = root;
        for (int i = 0; i < (int)prefix.size(); ++i) {
            int alphaNum = prefix[i] - 'a';
            if (cur->child[alphaNum] == NULL) // not found
                return false;
            cur = cur->child[alphaNum];
        }
        return true; // reach here, return true
    }
};
//* /Template

void solve() {
    int q; cin >> q;

    Trie X, Y;

    for(int _ = 0; _ < q; _++) {
        RAYA;
        int type; cin >> type;
        str S; cin >> S;
        dbg(type, S);

        if(type == 1) { //* X
            //* balance Y
            Y.balance(S);

            //* add to X
            X.insert(S);
        } else { //* Y
            //* check in X
            bool already = X.checkTerminal(S);
            dbg(already);

            if(!already) {
                Y.insert(S);
            }
        }

        dbg(Y.query());
        cout << Y.query() << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
}
