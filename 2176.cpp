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
    int countPairs(vector<int> &nums, int m)
    {
        vector<vector<int>> cnt(101);
        for (auto i = 0; i < nums.size(); ++i)
            cnt[nums[i]].push_back(i);

        int rv = 0;
        for (auto i = 0; i < 101; ++i)
            for (auto j = 0; j < cnt[i].size(); ++j)
                for (auto k = j + 1; k < cnt[i].size(); ++k)
                    if (cnt[i][j] * cnt[i][k] % m == 0)
                        ++rv;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPairs(vector<int>() = {3, 1, 2, 2, 2, 1, 3}, 2);
    cout << r << endl;
}