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
    vector<int> findDiagonalOrder(vector<vector<int>> &nums)
    {
        int m = nums.size(), n = 0;
        for (auto i = 0; i < m; ++i)
            n = max(n, (int)nums[i].size());
    
        vector<vector<int>> arr(m + n);
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < nums[i].size(); ++j)
                arr[i + j].push_back(nums[i][j]);

        vector<int> rv;
        for (auto &a : arr)
            for (auto it = rbegin(a); it != rend(a); ++it)
                rv.push_back(*it);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}