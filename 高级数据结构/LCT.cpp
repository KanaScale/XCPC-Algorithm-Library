const int N = 300005;

struct LinkCutTree {
    int ch[N][2]; // ch[x][0]左儿子，ch[x][1]右儿子
    int fa[N];    // Splay 树的父节点 / 原树的虚父节点
    int val[N];   // 节点自身的值
    int sum[N];   // Splay 子树的路径信息（如异或和、最大值等）
    int rev[N];   // 翻转懒标记

    bool isRoot(int x) {
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
    }

    void pushUp(int x) {
        sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ val[x];
    }

    void pushRev(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }

    void pushDown(int x) {
        if (rev[x]) {
            if (ch[x][0]) pushRev(ch[x][0]);
            if (ch[x][1]) pushRev(ch[x][1]);
            rev[x] = 0;
        }
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y];
        int k = (ch[y][1] == x);
        if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
        fa[x] = z;
        ch[y][k] = ch[x][k ^ 1];
        if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
        ch[x][k ^ 1] = y;
        fa[y] = x;
        pushUp(y);
        pushUp(x);
    }

    void updateMark(int x) {
        if (!isRoot(x)) updateMark(fa[x]);
        pushDown(x);
    }

    void splay(int x) {
        updateMark(x);
        while (!isRoot(x)) {
            int y = fa[x], z = fa[y];
            if (!isRoot(y)) {
                if ((ch[y][0] == x) ^ (ch[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = fa[x]) {
            splay(x);
            ch[x][1] = y;
            pushUp(x);
        }
    }
    
    void makeRoot(int x) {
        access(x);
        splay(x);
        pushRev(x);
    }

    int findRoot(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) {
            pushDown(x);
            x = ch[x][0];
        }
        splay(x);
        return x;
    }

    void split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
    }

    void link(int x, int y) {
        makeRoot(x);
        if (findRoot(y) != x) {
            fa[x] = y;
        }
    }

    void cut(int x, int y) {
        makeRoot(x);
        if (findRoot(y) == x && fa[y] == x && !ch[y][0]) {
            fa[y] = ch[x][1] = 0;
            pushUp(x);
        }
    }
};

/* ===============================================================================
LinkCutTree (LCT) 对外接口文档
===============================================================================

【一、动态树结构操作】

// 1. 在原树中，在节点 x 和节点 y 之间连接一条边。
// 若 x 和 y 已经在同一个连通块中（即 findRoot(x) == findRoot(y)），则不执行任何操作。
void link(int x, int y);

// 2. 在原树中，删除节点 x 和节点 y 之间的边。
// 若 x 和 y 之间原本就没有边，或者不在同一个连通块中，则不执行任何操作。
void cut(int x, int y);


【二、连通性与路径查询】

// 1. 提取并分离出节点 x 到节点 y 的路径。
// 操作后，节点 y 会被旋转到所在 Splay 的根节点。
// 此时 lct.sum[y] 存放的即为 x 到 y 路径上所有节点信息的总和（如异或和、最大值等）。
void split(int x, int y);

// 2. 寻找节点 x 所在原树的根节点。
// 主要用途：通过判断 findRoot(x) == findRoot(y) 来 $O(\log N)$ 地查询两点是否在同一个连通块中。
int findRoot(int x);

// 3. 将节点 x 强行变成全树的根节点（换根操作）。
// 常作为改变树形态、指定路径起点的基础操作。
void makeRoot(int x);


【三、单点信息更新规范】

// 注意：绝不能直接修改 lct.val[x]！必须遵循以下“三步走”规范，否则会破坏底层的二叉树信息维护。
// 若要将节点 x 的权值修改为 v：
// 
// lct.splay(x);       // 第一步：必须先将 x 转到所在 Splay 的根
// lct.val[x] = v;     // 第二步：修改自身权值
// lct.pushUp(x);      // 第三步：向上传递更新子树信息

=============================================================================== */