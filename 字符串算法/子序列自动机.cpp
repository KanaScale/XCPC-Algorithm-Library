int n = t.size();
vector<array<int, 26>> nxt(n + 1);
ranges::fill(nxt[n], n);
for (int i = n - 1; i >= 0; i--) {
    nxt[i] = nxt[i + 1];
    nxt[i][t[i] - 'a'] = i;
}