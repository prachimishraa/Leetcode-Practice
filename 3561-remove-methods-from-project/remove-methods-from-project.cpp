class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for (auto &e : invocations)
            adj[e[0]].push_back(e[1]);

        vector<int> vis(n, 0);

        function<void(int)> dfs = [&](int u) {
            vis[u] = 1;
            for (int v : adj[u])
                if (!vis[v])
                    dfs(v);
        };
        dfs(k);

        for (auto &e : invocations) {
            if (!vis[e[0]] && vis[e[1]]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (!vis[i])
                ans.push_back(i);
        return ans;
    }
};