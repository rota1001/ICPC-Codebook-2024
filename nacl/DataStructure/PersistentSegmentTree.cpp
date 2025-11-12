// cses Range Queries and Copies
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define pii pair<int, int>
#define N 200005
#define F first
#define S second
int n, ver = 1;
LL a[N];
struct Seg {
    LL v = 0;
    struct Seg *l = NULL, *r = NULL;
#define M (L + R >> 1)
    static const void init(Seg *node, int L = 1, int R = n) {
        if(L == R) {
            node->v = a[L];
            return;
        }
        node->l = new Seg();
        init(node->l, L, M);
        node->r = new Seg();
        init(node->r, M + 1, R);
        node->v = node->l->v + node->r->v;
    }
    static const void upd(Seg *node, int x, LL v, int L = 1,
                          int R = n) {
        if(L == R) {
            node->v = v;
            return;
        }
        if(x <= M)
            node->l = new Seg(*node->l),
            upd(node->l, x, v, L, M);
        else
            node->r = new Seg(*node->r),
            upd(node->r, x, v, M + 1, R);
        node->v = node->l->v + node->r->v;
    }
    static const LL qry(Seg *node, int l, int r, int L = 1,
                        int R = n) {
        if(l <= L && R <= r) return node->v;
        if(r <= M) return qry(node->l, l, r, L, M);
        if(M + 1 <= l) return qry(node->r, l, r, M + 1, R);
        return qry(node->l, l, M, L, M) +
               qry(node->r, M + 1, r, M + 1, R);
    }
} * tree[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q, i = 1, j, k;
    for(cin >> n >> q; i <= n; ++i) cin >> a[i];
    tree[1] = new Seg();
    Seg::init(tree[1]);
    for(; q--;) {
        cin >> i >> k;
        if(i == 1)
            cin >> i >> j, Seg::upd(tree[k], i, j);
        else if(i == 2)
            cin >> i >> j,
                cout << Seg::qry(tree[k], i, j) << "\n";
        else
            tree[++ver] = new Seg(*tree[k]);
    }
}