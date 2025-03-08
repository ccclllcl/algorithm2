#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;

#define lson (k << 1)
#define rson (k << 1 | 1)

const int N = 3 + 1e4;

int n, m;

namespace Dinic {
    struct Edge {
        int ver, next, flow;
    } E[N * 200];
    int head[N * 200], cur[N * 200], id = 1;
    int maxFlow;
    int d[N * 200];
    int nodeId; // 用于记录当前网络流，图中有多少个点
    const int s = ++nodeId; // 源
    const int t = ++nodeId; // 汇

    void addEdge(int u, int v, int f) {
        E[++id] = {v, head[u], f};
        head[u] = id;
        E[++id] = {u, head[v], 0};
        head[v] = id;
    }
    int bfs() {
        queue<int> q;
        q.push(s);
        for (int i = 1; i <= nodeId; ++i) {
            d[i] = 0;
            cur[i] = head[i];
        }
        d[s] = 1;
        while (q.size()) {
            int x = q.front();
            q.pop();
            for (int i = cur[x]; i; i = E[i].next) {
                int y = E[i].ver;
                if (E[i].flow && !d[y]) {
                    d[y] = d[x] + 1;
                    q.push(y);
                }
            }
        }
        return d[t];
    }
    int dfs(int x, int f) {
        if (x == t || f == 0) {
            return f;
        }
        int flow = 0;
        for (int &i = cur[x]; i && f > flow; i = E[i].next) {
            int y = E[i].ver;
            if (d[y] != d[x] + 1) {
                continue;
            }
            int t = dfs(y, min(f - flow, E[i].flow));
            flow += t;
            E[i].flow -= t;
            E[i ^ 1].flow += t;
            if (f == flow) {
                return flow;
            }
        }
        return flow;
    }
    int run() {
        while (bfs()) {
            maxFlow += dfs(s, 1e9);
        }
        return maxFlow;
    }
};  // namespace Dinic

namespace Tree {
    struct E {
        int y, id; // 边(x,y)，在网络流建图中点编号为id
    };
    vector<E> edge[N];
    int sz[N], top[N], fa[N], son[N], dfn[N], d[N], id;
    int p[N]; // 边(x,y)，d[x]<d[y]，id存到p[y]
    int w[N]; // w[i]含义，p[x]的dfs序为i，w[i]就是p[x]

    struct TreeNode {
        int l, r;
        int v; // [l,r]区间代表的点在网络流建图中的点的编号
    } tr[N << 2];

    void addEdge(int u, int v, int id) {
        edge[u].push_back({v, id});
        edge[v].push_back({u, id});
    }

    void dfs1(int x, int fa) {
        d[x] = d[fa] + 1;
        sz[x] = 1;
        Tree::fa[x] = fa;
        for (auto &[y, id] : edge[x]) {
            if (y == fa) {
                continue;
            }
            p[y] = id;
            dfs1(y, x);
            sz[x] += sz[y];
            if (sz[y] > sz[son[x]]) {
                son[x] = y;
            }
        }
    }

    void dfs2(int x, int fa, int topf) {
        dfn[x] = ++id;
        top[x] = topf;
        w[id] = p[x];
        if (son[x]) {
            dfs2(son[x], x, topf);
        }
        for (auto &[y, id] : edge[x]) {
            if (y == fa || y == son[x]) {
                continue;
            }
            dfs2(y, x, y);
        }
    }

    void segmentTreeBuild(int k, int l, int r, vector<int> ve) {
        tr[k].l = l;
        tr[k].r = r;
        tr[k].v = ++Dinic::nodeId;
        ve.push_back(tr[k].v);
        if (l == r) {
            if (r != 1) { // 1号点没有存边
                for (auto x : ve) { // 将线段树区间包含r的区间，和r连边
                    Dinic::addEdge(x, w[r], 1e9);
                }
            }
            return;
        }
        int mid = l + r >> 1;
        segmentTreeBuild(lson, l, mid, ve);
        segmentTreeBuild(rson, mid + 1, r, ve);
    }

    void update(int k, int l, int r, int t) {
        if (l <= tr[k].l && tr[k].r <= r) {
            Dinic::addEdge(t, tr[k].v, 1e9);
            return;
        }
        int mid = tr[k].l + tr[k].r >> 1;
        if (l <= mid) {
            update(lson, l, r, t);
        }
        if (r > mid) {
            update(rson, l, r, t);
        }
    }

    void addDinicEdge(int u, int v, int f) {
        int t = ++Dinic::nodeId;
        Dinic::addEdge(Dinic::s, t, f);
        while (top[u] != top[v]) {
            if (d[top[u]] < d[top[v]]) {
                swap(u, v);
            }
            update(1, dfn[top[u]], dfn[u], t);
            u = fa[top[u]];
        }
        if (d[u] > d[v]) {
            swap(u, v);
        }
        if (dfn[u] + 1 <= dfn[v]) {
            // u这个存在边不在范围内，不能写成update(1, dfn[u], dfn[v], t);
            update(1, dfn[u] + 1, dfn[v], t);
        }
    }
}  // namespace Tree

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        Tree::addEdge(u, v, ++Dinic::nodeId);
        Dinic::addEdge(Dinic::nodeId, Dinic::t, w);
    }
    Tree::dfs1(1, 0);
    Tree::dfs2(1, 0, 1);
    Tree::segmentTreeBuild(1, 1, n, {});

    int ans = 0;

    while (m--) {
        int s, t, a, b;
        cin >> s >> t >> a >> b;
        if (a - b > 0) {
            Tree::addDinicEdge(s, t, a - b);
            ans += a - b;
        }
    }

    ans -= Dinic::run();

    cout << ans << endl;

    return 0;
}