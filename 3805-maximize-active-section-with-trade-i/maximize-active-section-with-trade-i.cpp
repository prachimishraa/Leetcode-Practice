class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int active = 0;
        for (char c : s)
            if (c == '1') active++;
        string t = "1" + s + "1";

        vector<pair<char,int>> runs;

        for (char c : t) {
            if (runs.empty() || runs.back().first != c)
                runs.push_back({c,1});
            else
                runs.back().second++;
        }
        int ans = active;

        for (int i = 1; i + 1 < runs.size(); i++) {
            if (runs[i].first == '1' &&
                runs[i-1].first == '0' &&
                runs[i+1].first == '0') {

                int gain = runs[i-1].second + runs[i+1].second;
                ans = max(ans, active + gain);
            }
        }
        return ans;
    }
};