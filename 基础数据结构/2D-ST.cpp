struct ST2D {
    int n, m;
    vector<int> lgN, lgM;

    // st[kx][ky][i][j]
    // 表示以 (i, j) 为左上角，大小为 2^kx * 2^ky 的矩形信息
    vector<vector<vector<vector<int>>>> st;

    int merge(int a, int b) {
        return max(a, b);
        // return min(a, b);
    }

    void build(const vector<vector<int>>& a) {
        n = (int)a.size();
        m = (int)a[0].size();

        lgN.assign(n + 1, 0);
        lgM.assign(m + 1, 0);

        for (int i = 2; i <= n; i++) {
            lgN[i] = lgN[i >> 1] + 1;
        }

        for (int i = 2; i <= m; i++) {
            lgM[i] = lgM[i >> 1] + 1;
        }

        int KN = lgN[n] + 1;
        int KM = lgM[m] + 1;

        st.assign(
            KN,
            vector<vector<vector<int>>>(
                KM,
                vector<vector<int>>(
                    n,
                    vector<int>(m)
                )
            )
        );

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                st[0][0][i][j] = a[i][j];
            }
        }

        for (int kx = 0; kx < KN; kx++) {
            for (int ky = 0; ky < KM; ky++) {
                if (kx == 0 && ky == 0) continue;

                int lenX = 1 << kx;
                int lenY = 1 << ky;

                for (int i = 0; i + lenX <= n; i++) {
                    for (int j = 0; j + lenY <= m; j++) {
                        if (kx == 0) {
                            st[kx][ky][i][j] = merge(
                                st[kx][ky - 1][i][j],
                                st[kx][ky - 1][i][j + (1 << (ky - 1))]
                            );
                        } else if (ky == 0) {
                            st[kx][ky][i][j] = merge(
                                st[kx - 1][ky][i][j],
                                st[kx - 1][ky][i + (1 << (kx - 1))][j]
                            );
                        } else {
                            int v1 = st[kx - 1][ky - 1][i][j];
                            int v2 = st[kx - 1][ky - 1][i + (1 << (kx - 1))][j];
                            int v3 = st[kx - 1][ky - 1][i][j + (1 << (ky - 1))];
                            int v4 = st[kx - 1][ky - 1][i + (1 << (kx - 1))][j + (1 << (ky - 1))];

                            st[kx][ky][i][j] = merge(
                                merge(v1, v2),
                                merge(v3, v4)
                            );
                        }
                    }
                }
            }
        }
    }

    // 查询子矩形 [(x1, y1), (x2, y2)]
    // 下标从 0 开始，且 x1 <= x2, y1 <= y2
    int query(int x1, int y1, int x2, int y2) {
        int kx = lgN[x2 - x1 + 1];
        int ky = lgM[y2 - y1 + 1];

        int nx = x2 - (1 << kx) + 1;
        int ny = y2 - (1 << ky) + 1;

        int v1 = st[kx][ky][x1][y1];
        int v2 = st[kx][ky][nx][y1];
        int v3 = st[kx][ky][x1][ny];
        int v4 = st[kx][ky][nx][ny];

        return merge(
            merge(v1, v2),
            merge(v3, v4)
        );
    }
};