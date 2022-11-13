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
    long long dp[101][101] = {};
    long long dfs(vector<int> &robot, vector<vector<int>> &factory, int i, int j)
    {
        if (i >= robot.size())
            return 0;

        if (j >= factory.size())
            return 1e15;

        long long pos = factory[j][0], limit = factory[j][1], sum = 0;
        if (!dp[i][j])
        {
            dp[i][j] = dfs(robot, factory, i, j + 1);
            for (auto k = 0; k < limit && i + k < robot.size(); ++k)
            {
                sum += abs(pos - robot[i + k]);
                dp[i][j] = min(dp[i][j], sum + dfs(robot, factory, i + k + 1, j + 1));
            }
            ++dp[i][j];
        }
        return dp[i][j] - 1;
    }

public:
    long long minimumTotalDistance(vector<int> &robot, vector<vector<int>> &factory)
    {
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));
        return dfs(robot, factory, 0, 0);
    }
};


int main()
{
    Solution sol;
    int r;

    r = sol.minimumTotalDistance(vector<int>() = {9, 11, 99, 101}, vector<vector<int>>() = {{10, 1}, {7, 1}, {14, 1}, {100, 1}, {96, 1}, {103, 1}});
    cout << r << endl;

    r = sol.minimumTotalDistance(vector<int>() = {0, 4, 6}, vector<vector<int>>() = {{2, 2}, {6, 2}});
    cout << r << endl;
}