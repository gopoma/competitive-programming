// https://ideone.com/A6roDp

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

struct node {
	int val;

	node(){
		val = 0;
	}

	node(int x) {
		val = x;
	}

	node operator + (const node &rhs) const {
		return node(max(val, rhs.val));
	}
};

struct action {
	int val;

	action(){
		val = 0;
	}

	action(int x) {
		val = x;
	}

	action operator * (const action &rhs) const {
		return action(max(val, rhs.val));
	}

	node operator * (const node &rhs) const {
		return node(max(rhs.val, val));
	}

	bool operator == (const action &rhs) const {
		return val == rhs.val;
	}

	bool operator != (const action &rhs) const {
		return !(*this == rhs);
	}
};

int n;
int q;
node NIL_NODE;
node st[4 * N];
action NIL_ACTION;
action lazy[4 * N];

void apply_action(action z, int pos, int l, int r) {
	st[pos] = z * st[pos];
	lazy[pos] = z * lazy[pos];
}

void push(int pos, int l, int r) {
	if(lazy[pos] != NIL_ACTION) {
		st[2 * pos] = lazy[pos] * st[2 * pos];
		lazy[2 * pos] = lazy[pos] * lazy[2 * pos];
		st[2 * pos + 1] = lazy[pos] * st[2 * pos + 1];
		lazy[2 * pos + 1] = lazy[pos] * lazy[2 * pos + 1];
		lazy[pos] = NIL_ACTION;
	}
}

void update(int x, int y, action z, int pos = 1, int l = 0, int r = n - 1) {
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y) {
		apply_action(z, pos, l, r);
		return;
	}
	push(pos, l, r);
	int mi = (l + r) / 2;
	update(x, y, z, 2 * pos, l, mi);
	update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

node query(int x, int y, int pos = 1, int l = 0, int r = n - 1) {
	if(y < l or r < x or x > y) return NIL_NODE;
	if(x <= l and r <= y) return st[pos];
	push(pos, l, r);
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int main() {
	scanf("%d %d", &n, &q);
	while(q--) {
		int op;
		scanf("%d", &op);
		if(op == 1) {
			int l, r, v;
			scanf("%d %d %d", &l, &r, &v);
			r--;
			update(l, r, action(v));
		}
		else {
			int i;
			scanf("%d", &i);
			printf("%d\n", query(i, i).val);
		}
	}
	return 0;
}
