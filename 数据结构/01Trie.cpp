const int N = 500005; 
const int M = 16000005; //4*N
const int HB = 30;
int tr[M][2];
int cnt[M];
int tot = 1;

void insert(int v) {
    int u = 1;
    cnt[u]++;  
    for (int i = HB; i >= 0; i--) {
        int b = (v >> i) & 1;
        if (!tr[u][b]) tr[u][b] = ++tot;
        u = tr[u][b];
        cnt[u]++;
    }
}

void remove(int v) {
    int u = 1;
    cnt[u]--;  
    for (int i = HB; i >= 0; i--) {
        int b = (v >> i) & 1;
        u = tr[u][b];
        cnt[u]--;
    }
}

int max_xor(int v) { 
    if (cnt[1] == 0) return 0; 
    
    int u = 1;
    int ans = 0;
    for (int i = HB; i >= 0; i--) {
        int b = (v >> i) & 1; 
        if (tr[u][b ^ 1] && cnt[tr[u][b ^ 1]]) {
            ans |= (1 << i);
            u = tr[u][b ^ 1];
        }  
        else if (tr[u][b] && cnt[tr[u][b]]) {
            u = tr[u][b];
        } else {
            break;
        }
    }
    return ans;
}