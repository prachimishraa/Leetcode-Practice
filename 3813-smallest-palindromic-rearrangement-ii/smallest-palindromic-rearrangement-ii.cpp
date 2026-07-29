class Solution {
public:
    const long long LIMIT = 1000000;

    long long comb(int n, int r) {
        if (r > n) return 0;
        if (r > n - r) r = n - r;

        long long res = 1;
        for (int i = 1; i <= r; i++) {
            res = res * (n - r + i) / i;
            if (res > LIMIT) return LIMIT + 1;
        }
        return res;
    }
    long long countWays(vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ways = 1;
        int rem = total;

        for (int c : cnt) {
            if (c == 0) continue;
            ways *= comb(rem, c);

            if (ways > LIMIT)
                ways = LIMIT + 1;

            rem -= c;
        }
        return ways;
    }
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2)
                mid.push_back(char('a' + i));
        }
        if (countWays(half) < k)
            return "";
        int len = 0;
        for (int x : half) len += x;

        string left;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0)
                    continue;
                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }
                k -= ways;
                half[c]++;
            }
        }
        string right = left;
        reverse(right.begin(), right.end());
        return left + mid + right;
    }
};