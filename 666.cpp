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
    void dfs(int d, int p, int curr, int &sum)
    {
        if (nodes[d + 1][p * 2] == -1 && nodes[d + 1][p * 2 + 1] == -1)
        {
            sum += curr + nodes[d][p];
            return;
        }

        if (nodes[d + 1][p * 2] != -1)
            dfs(d + 1, p * 2, curr + nodes[d][p], sum);
        if (nodes[d + 1][p * 2 + 1] != -1)
            dfs(d + 1, p * 2 + 1, curr + nodes[d][p], sum);
    }

    vector<vector<int>> nodes;

public:
    int pathSum(vector<int> &nums)
    {
        nodes = vector<vector<int>>(6, vector<int>(17, -1));
        for (auto n : nums)
        {
            int v = n % 10;
            n /= 10;
            int p = n % 10;
            n /= 10;
            int d = n % 10;
            nodes[d - 1][p - 1] = v;
        }
        int sum = 0;
        dfs(0, 0, 0, sum);
        return sum;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.pathSum(vector<int>() = {115, 215, 224, 325, 336, 446, 458});
    cout << r << endl;
}