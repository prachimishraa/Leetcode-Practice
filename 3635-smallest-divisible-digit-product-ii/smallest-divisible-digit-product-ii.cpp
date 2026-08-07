#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int get_min_digits_needed(int cnt2, int cnt3, int cnt5, int cnt7) {
        int digits = cnt5 + cnt7;
        
        int n9 = cnt3 / 2;
        cnt3 %= 2;
        
        int n8 = cnt2 / 3;
        cnt2 %= 3;
        
        if (cnt3 == 1 && cnt2 == 2) {
            digits += 2;
            cnt3 = 0;
            cnt2 = 0;
        } else if (cnt3 == 1 && cnt2 == 1) { 
            digits += 1;
            cnt3 = 0;
            cnt2 = 0;
        }
        
        digits += cnt3;
        
        int n4 = cnt2 / 2;
        cnt2 %= 2;
        digits += n4 + cnt2;
        
        digits += n9 + n8;
        return digits;
    }

    string construct_smallest_suffix(int cnt2, int cnt3, int cnt5, int cnt7, int length) {
        string suff = "";
        
        while (cnt3 >= 2) { suff += '9'; cnt3 -= 2; }

        while (cnt2 >= 3) { suff += '8'; cnt2 -= 3; }

        while (cnt7 > 0) { suff += '7'; cnt7--; }
        
        if (cnt3 == 1 && cnt2 == 2) { suff += '6'; suff += '2'; cnt3 = 0; cnt2 = 0; }
        else if (cnt3 == 1 && cnt2 == 1) { suff += '6'; cnt3 = 0; cnt2 = 0; }
        else if (cnt3 == 1) { suff += '3'; cnt3 = 0; }
        
        while (cnt5 > 0) { suff += '5'; cnt5--; }

        while (cnt2 >= 2) { suff += '4'; cnt2 -= 2; }
        if (cnt2 == 1) { suff += '2'; cnt2--; }
        
        while (suff.length() < length) {
            suff += '1';
        }
        
        sort(suff.begin(), suff.end());
        return suff;
    }

public:
    string smallestNumber(string num, long long t) {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        long long temp = t;
        
        while (temp % 2 == 0) { c2++; temp /= 2; }
        while (temp % 3 == 0) { c3++; temp /= 3; }
        while (temp % 5 == 0) { c5++; temp /= 5; }
        while (temp % 7 == 0) { c7++; temp /= 7; }
        
        if (temp > 1) return "-1";
        
        int n = num.length();
        
        vector<int> p2(n + 1, 0), p3(n + 1, 0), p5(n + 1, 0), p7(n + 1, 0);
        int first_zero = -1;
        
        for (int i = 0; i < n; i++) {
            p2[i+1] = p2[i]; p3[i+1] = p3[i]; p5[i+1] = p5[i]; p7[i+1] = p7[i];
            if (num[i] == '0') {
                if (first_zero == -1) first_zero = i;
                continue;
            }
            int d = num[i] - '0';
            while (d % 2 == 0) { p2[i+1]++; d /= 2; }
            while (d % 3 == 0) { p3[i+1]++; d /= 3; }
            while (d % 5 == 0) { p5[i+1]++; d /= 5; }
            while (d % 7 == 0) { p7[i+1]++; d /= 7; }
        }
        
        if (first_zero == -1 && p2[n] >= c2 && p3[n] >= c3 && p5[n] >= c5 && p7[n] >= c7) {
            return num;
        }
        
        int limit = (first_zero != -1) ? first_zero : n - 1;
        
        for (int i = limit; i >= 0; i--) {
            int start_digit = num[i] - '0' + 1;
            for (int d = start_digit; d <= 9; d++) {
                int n2 = max(0, c2 - p2[i]);
                int n3 = max(0, c3 - p3[i]);
                int n5 = max(0, c5 - p5[i]);
                int n7 = max(0, c7 - p7[i]);
                
                int val = d;
                while (val % 2 == 0) { n2 = max(0, n2 - 1); val /= 2; }
                while (val % 3 == 0) { n3 = max(0, n3 - 1); val /= 3; }
                while (val % 5 == 0) { n5 = max(0, n5 - 1); val /= 5; }
                while (val % 7 == 0) { n7 = max(0, n7 - 1); val /= 7; }
                
                int rem_len = n - 1 - i;
                if (get_min_digits_needed(n2, n3, n5, n7) <= rem_len) {
                    string ans = num.substr(0, i);
                    ans += to_string(d);
                    ans += construct_smallest_suffix(n2, n3, n5, n7, rem_len);
                    return ans;
                }
            }
        }
        
        int total_needed_len = max(n + 1, get_min_digits_needed(c2, c3, c5, c7));
        return construct_smallest_suffix(c2, c3, c5, c7, total_needed_len);
    }
};
