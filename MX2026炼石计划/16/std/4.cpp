#include <bits/stdc++.h>
#define FILE(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define all(x) (x).begin(),(x).end()

using ll = long long;
using std::cerr;

const int N = 1e5 + 20;

struct edge {
    int from, to;
}eg[N << 1];

int front[N], num;
void add(int x, int y) {eg[++ num] = (edge){front[x], y}; front[x] = num;}

int fa[N], siz[N], dep[N], top[N], son[N], up[N][20][2], down[N][20][2];

struct SgNode {
    int o, sg, dep;
    SgNode(int o, int sg, int dep) : o(o), sg(sg), dep(dep) {}
};

struct Args {
    int arg1;
    SgNode arg2;
    Args(int arg1, SgNode arg2) : arg1(arg1), arg2(arg2) {}
};

std::deque<SgNode> chain[N];
std::deque<Args> delChain, addChain, delVertex[N], addVertex[N], modifyVertex, spChain;
int sp[N];
int sgTot[N][20][2], maxs[N][3];

void del_chain(int idx) { delChain.push_back(Args(idx, chain[idx].front())), chain[idx].pop_front(); }
void add_chain(int idx, SgNode val) { addChain.push_back(Args(idx, chain[idx].front())); chain[idx].push_front(val); }
void del_vertex(int idx, SgNode val) { delVertex[idx].push_back(Args(0, val)); modifyVertex.push_back(Args(idx, val));}
void add_vertex(int idx, SgNode val) { addVertex[idx].push_back(Args(0, val)); modifyVertex.push_back(Args(idx, val));}
void add_sp(int idx, int node) { sp[idx] = node; spChain.push_back(Args(node, SgNode(0, 0, 0))); }
void rebuild() {
    while(addChain.size()) {
        Args args = addChain.back(); addChain.pop_back();
        chain[args.arg1].pop_front();
    }
    while(delChain.size()) {
        Args args = delChain.back(); delChain.pop_back();
        chain[args.arg1].push_front(args.arg2);
    }
    for (auto [idx, val] : modifyVertex) addVertex[idx].clear(), delVertex[idx].clear();
    for (auto [idx, val] : spChain) sp[idx] = 0;
    modifyVertex.clear();
    spChain.clear();
}

int dfn[N], tot;
void dfs1(int o, int from) {
    fa[o] = from;
    siz[o] = 1;
    dep[o] = dep[from] + 1;
    dfn[o] = ++ tot;
    for (int i = front[o]; i; i = eg[i].from) {
        int to = eg[i].to;
        if(to == from) continue;
        dfs1(to, o);
        siz[o] += siz[to];
        if(siz[to] > siz[son[o]]) son[o] = to;
    }
}

void dfs2(int o, int tp) {
    top[o] = tp;
    if(son[o]) dfs2(son[o], tp);

    for (int i = front[o]; i; i = eg[i].from) {
        int to = eg[i].to;
        if(to == fa[o] || to == son[o]) continue;
        dfs2(to, to);
    }
}

int LCA(int x, int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

SgNode merge(SgNode node1, SgNode node2) {
    if(node1.sg < node2.sg) node1.sg = node2.sg, node1.dep = node2.dep;
    else if(node1.sg == node2.sg && node1.dep != node2.dep) ++ node1.sg, node1.dep = dep[node1.o] & 1;
    return node1;
}

SgNode get_sg(int o, SgNode extra) {
    SgNode re = SgNode(o, -100, dep[o] & 1);
    std::vector<int> val;

    for (auto dels : delVertex[o]) if(dels.arg2.sg >= 0) -- sgTot[o][dels.arg2.sg][dels.arg2.dep];
    for (auto adds : addVertex[o]) if(adds.arg2.sg >= 0) ++ sgTot[o][adds.arg2.sg][adds.arg2.dep], val.push_back(adds.arg2.sg);
    if(extra.sg >= 0) ++ sgTot[o][extra.sg][extra.dep], val.push_back(extra.sg);

    for (int i = 0; i < 3; ++ i) val.push_back(maxs[o][i]);
    sort(all(val));

    for (int i = val.size() - 1; ~i; -- i) {
        if(sgTot[o][val[i]][0]) re = merge(re, SgNode(o, val[i], 0));
        if(sgTot[o][val[i]][1]) re = merge(re, SgNode(o, val[i], 1));
        if(re.sg >= 0) break;
    }

    
    for (auto dels : delVertex[o]) if(dels.arg2.sg >= 0) ++ sgTot[o][dels.arg2.sg][dels.arg2.dep];
    for (auto adds : addVertex[o]) if(adds.arg2.sg >= 0) -- sgTot[o][adds.arg2.sg][adds.arg2.dep];
    if(extra.sg >= 0) -- sgTot[o][extra.sg][extra.dep];

    return re;
}

void pushup_chain(int o, int type) {
    int idx = top[o];
    add_sp(idx, o);

    if(fa[top[o]] && chain[idx].size()) del_vertex(fa[top[o]], chain[idx].front());

    while(chain[idx].size() && dep[chain[idx].front().o] <= dep[o]) del_chain(idx);
    SgNode sg = get_sg(o, type ? chain[idx].front() : SgNode(0, -100, 0));
    if(sg.sg < 0) sg = SgNode(o, 0, dep[o] & 1);
    add_chain(idx, sg);
    if(o != top[o]) {
        o = fa[o];
        while(up[o][sg.sg][sg.dep]) {
            o = up[o][sg.sg][sg.dep];
            sg = get_sg(o, sg);
            add_chain(idx, sg);
        }
    }

    if(fa[top[o]] && chain[idx].size()) add_vertex(fa[top[o]], chain[idx].front());
}

SgNode pushdown_chain(int o, int ed, SgNode sg) {
    if(sg.sg < 0 && o != ed) sg = get_sg(o, sg);
    if(sg.sg < 0 && o != ed) sg = SgNode(o, 0, dep[o] & 1);
    if(sp[top[o]] && dep[o] <= dep[sp[top[o]]] && dep[sp[top[o]]] < dep[ed]) {
        while(down[o][sg.sg][sg.dep] && dep[down[o][sg.sg][sg.dep]] < dep[sp[top[o]]]) {
            o = down[o][sg.sg][sg.dep];
            sg = get_sg(o, sg);
        }
        o = sp[top[o]];
        sg = get_sg(o, sg);
        o = son[o];
    }
    
    while(o != ed && down[o][sg.sg][sg.dep] && dep[down[o][sg.sg][sg.dep]] < dep[ed]) {
        o = down[o][sg.sg][sg.dep];
        sg = get_sg(o, sg);
    }

    if(son[ed]) {
        for (auto chainSg : chain[top[ed]]) if(dep[chainSg.o] > dep[ed]) {
            add_vertex(ed, chainSg);
            break;
        }
    }

    sg = get_sg(ed, sg);
    if(sg.sg < 0) sg.sg = 0, sg.dep = dep[ed] & 1;
    return sg;
}

void pushup_root(int o, int type) {
    while(o) {
        pushup_chain(o, type);
        type = 1;
        o = fa[top[o]];
    }
}

SgNode pushdown_root(int o, int rt) {
    assert(o);
    if(top[o] != top[rt]) {
        if (fa[top[o]]) del_vertex(fa[top[o]], chain[top[o]].front());
        SgNode sg = pushdown_root(fa[top[o]], rt);
        return pushdown_chain(top[o], o, sg);
    } else return pushdown_chain(rt, o, SgNode(0, -100, 0));
}

void build(int o, int from) {

    for (int i = front[o]; i; i = eg[i].from) {
        int to = eg[i].to;
        if(to == from || to == son[o]) continue;
        build(to, o);
    }
    for (auto adds : addVertex[o]) if(adds.arg2.sg >= 0) ++ sgTot[o][adds.arg2.sg][adds.arg2.dep];
    addVertex[o].clear();

    int temp = 0;
    for (int i = 19; i; -- i) {
        if(sgTot[o][i][0] + sgTot[o][i][1]) maxs[o][temp ++] = i;
        if(temp >= 3) break;
    }

    for (int i = 0; i <= 19; ++ i) {
        if(son[fa[o]] == o) {
            up[o][i][0] = up[fa[o]][i][0];
            up[o][i][1] = up[fa[o]][i][1];
        }

        if(i < maxs[o][0]) up[o][i][0] = up[o][i][1] = o;
        if(i == maxs[o][0]) {
            if(sgTot[o][i][0]) up[o][i][1] = o;
            if(sgTot[o][i][1]) up[o][i][0] = o;
        }
    }

    if(son[o]) build(son[o], o);
    else pushup_chain(o, 0);

    for (int i = 0; i <= 19; ++ i) {
        if(son[o]) {
            down[o][i][0] = down[son[o]][i][0];
            down[o][i][1] = down[son[o]][i][1];
        }

        if(i < maxs[o][0]) down[o][i][0] = down[o][i][1] = o;
        if(i == maxs[o][0]) {
            if(sgTot[o][i][0]) down[o][i][1] = o;
            if(sgTot[o][i][1]) down[o][i][0] = o;
        }
    }
}

void init(int n) {
    num = 0;
    memset(front, 0, sizeof(int) * (n + 10));
    memset(son, 0, sizeof(int) * (n + 10));
    memset(sp, 0, sizeof(int) * (n + 10));
    memset(up, 0, sizeof(int) * (n + 10) * 40);
    memset(down, 0, sizeof(int) * (n + 10) * 40);
    memset(sgTot, 0, sizeof(int) * (n + 10) * 40);
    memset(maxs, 0, sizeof(int) * (n + 10) * 3);
    for (int i = 1; i <= n; ++ i) chain[i].clear();
}

void solve() {
    int n;
    std::cin >> n;
    init(n);

    for (int i = 1; i < n; ++ i) {
        int x, y;
        std::cin >> x >> y;
        add(x, y);
        add(y, x);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 0);

    spChain.clear();
    addChain.clear();
    delChain.clear();
    modifyVertex.clear();

    int q;
    std::cin >> q;

    for (int i = 1; i <= q; ++ i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if(dep[x1] < dep[y1]) std::swap(x1, y1);

        if(x1 != son[y1]) del_vertex(y1, chain[x1].front());
        pushup_root(y1, (x1 != son[y1]));
        if(x1 == son[y1]) son[y1] = 0;

        if(LCA(x2, x1) != x1) std::swap(x2, y2);
        
        SgNode sg1 = pushdown_root(x2, x1), sg2 = pushdown_root(y2, 1);

        if(((sg1.sg << 1) | (sg1.dep ^ (dep[x2] & 1))) == ((sg2.sg << 1) | (sg2.dep ^ (dep[y2] & 1)))) std::cout << "Alice\n";
        else std::cout << "Bob\n";

        if(son[y1] == 0) son[y1] = x1;
        rebuild();
    }
}

int main() {
    FILE("cutting");
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    int T;
    std::cin >> T;
    while(T --) solve();
}