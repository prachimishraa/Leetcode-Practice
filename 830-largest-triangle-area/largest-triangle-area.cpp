class Solution {
public:
    double area(vector<int>& A, vector<int>& B, vector<int>& C) {
        return abs(
            A[0] * (B[1] - C[1]) +
            B[0] * (C[1] - A[1]) +
            C[0] * (A[1] - B[1])
        ) / 2.0;
    }

    double largestTriangleArea(vector<vector<int>>& points) {
        double maxArea = 0.0;
        int n = points.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    maxArea = max(maxArea,
                                  area(points[i], points[j], points[k]));
                }
            }
        }
        return maxArea;
    }
};