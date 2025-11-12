#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = 8e18;
#define N 505
#define pb push_back
struct pp {
    int from, to;
    ll cap, flow;
};
int t, lvl[N], p[N];
vector<int> g[N];
vector<pp> edge;
int bfs(int s) {
    queue<int> q;
    for(q.push(s), lvl[s] = 1; !q.empty(); q.pop()) {
        int u = q.front();
        for(int e : g[u]) {
            int v = edge[e].to;
            if(lvl[v] || !edge[e].flow) continue;
            lvl[v] = lvl[u] + 1;
            q.push(v);
        }
    }
    return lvl[t];
}
ll dfs(int u, ll f = inf) {
    if(u == t || !f) return f;
    ll ans = 0;
    for(int &i = p[u]; i < g[u].size(); ++i) {
        pp &e = edge[g[u][i]], &b = edge[g[u][i] ^ 1];
        if(lvl[e.to] == lvl[u] + 1) {
            ll c = dfs(e.to, min(e.flow, f));
            e.flow -= c;
            b.flow += c;
            f -= c;
            ans += c;
        }
    }
    return ans;
}
ll dinic(int s) {
    ll ans = 0;
    for(; bfs(s); memset(lvl, 0, sizeof lvl))
        for(ll k; k = (memset(p, 0, sizeof(p)), dfs(s));)
            ans += k;
    return ans;
}
int main() {
    ios::sync_with_stdio(0); //任意圖上複雜度 V^2E
    cin.tie(0); //邊容量為 1 時 min(V^{\frac{2}{3}},\sqrt E)E
    cout.tie(0); //二分圖最大匹配 E\sqrt V(是下面這行的特例)
    int n, m, cnt = 0; //邊容量 1 時，除源匯點滿足入度或出度
    for(cin >> n >> m; m--;) { //都是 1，則為 E\sqrt V
        int u, v;
        ll f;
        cin >> u >> v >> f;
        g[u].pb(cnt++);
        g[v].pb(cnt++);
        edge.pb({u, v, f, f});
        edge.pb({v, u, 0, 0});
    }
    t = n;
    cout << dinic(1);
}