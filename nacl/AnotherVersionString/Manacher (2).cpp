#define T(x) ((x)&1 ? s[(x) >> 1] : '.')
int ex(string &s, int l, int r, int n) {
    int i = 0;
    while(l - i >= 0 && r + i < n && T(l - i) == T(r + i)) ++i;
    return i;
}
int manacher(string s, int n) {
    n = 2 * n + 1;
    int mx = 0;
    int center = 0;
    vector<int> r(n);
    int ans = 1;
    r[0] = 1;
    for(int i = 1; i < n; i++) {
        int ii = center - (i - center);
        int len = mx - i + 1;
        if(i > mx) {
            r[i] = ex(s, i, i, n);
            center = i;
            mx = i + r[i] - 1;
        } else if(r[ii] == len) {
            r[i] = len + ex(s, i - len, i + len, n);
            center = i;
            mx = i + r[i] - 1;
        } else {
            r[i] = min(r[ii], len);
        }
        ans = max(ans, r[i]);
    }
    return ans - 1;
}