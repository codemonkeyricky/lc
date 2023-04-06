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
    vector<int> sumEvenAfterQueries(vector<int> &nums, vector<vector<int>> &queries)
    {
        int sum = 0;
        for (auto &n : nums)
            if (n % 2 == 0)
                sum += n;

        vector<int> rv;
        for (auto &q : queries)
        {
            int v = q[0];
            int k = q[1];
            if (nums[k] % 2 == 0)
                sum -= nums[k];
            nums[k] += v;
            if (nums[k] % 2 == 0)
                sum += nums[k];
            rv.push_back(sum);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.sumEvenAfterQueries(vector<int>() = {1,2,3,4}, vector<vector<int>>() = {{1,0}, {-3,1}, {-4, 0}, {2,3}});
}