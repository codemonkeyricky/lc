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
    int beautifulSubsets(vector<int> &nums, int k)
    {
        sort(begin(nums), end(nums));
        int n = nums.size();

        vector<int> conflicts;
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
                if (nums[i] + k == nums[j])
                    conflicts.push_back((1 << i) | (1 << j));

        int rv = 0;
        for (auto mask = 1; mask < (1 << n); ++mask)
        {
            int valid = true;
            for (auto &conflict : conflicts)
                if ((mask & conflict) == conflict)
                {
                    valid = false;
                    break;
                }
            if (valid)
                ++rv;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.beautifulSubsets(vector<int>() = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 1);
    // cout << r << endl;

    // r = sol.beautifulSubsets(vector<int>() = {20, 14, 22, 1, 4, 11, 21, 19, 29, 25, 12, 18, 9, 15, 23, 6, 27, 16, 26, 5}, 13);
    // cout << r << endl;

    r = sol.beautifulSubsets(vector<int>() = {2, 4, 6}, 2);
    cout << r << endl;
}