int n = s.size();
vector<array<int, 26>> nxt(n + 1);
fill(all(nxt[n]), n);
for (int i = n - 1; i >= 0; i--) {
    nxt[i] = nxt[i + 1];
    nxt[i][s[i] - 'a'] = i;
}