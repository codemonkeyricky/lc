#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

class Solution
{
public:
    int kthLargestValue(vector<vector<int>> &mat, int k)
    {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        vector<int> sum; 
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; sum.push_back(dp[i][j++]))
                dp[i][j] = (i ? dp[i - 1][j] : 0) ^
                           (j ? dp[i][j - 1] : 0) ^
                           (i && j ? dp[i - 1][j - 1] : 0) ^
                           mat[i][j];

        nth_element(begin(sum), begin(sum) + k - 1, end(sum), greater<int>{});
        return sum[k - 1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.kthLargestValue(vector<vector<int>>() = {{8, 10, 5, 8, 5, 7, 6, 0, 1, 4, 10, 6, 4, 3, 6, 8, 7, 9, 4, 2}}, 2);
    cout << r << endl;

    r = sol.kthLargestValue(vector<vector<int>>() = {{5, 2}, {1, 6}}, 4);
    cout << r << endl;

    r = sol.kthLargestValue(vector<vector<int>>() = {{5, 2}, {1, 6}}, 1);
    cout << r << endl;
}