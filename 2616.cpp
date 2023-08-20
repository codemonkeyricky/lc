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
    int minimizeMax(vector<int> &nums, int p)
    {
        sort(begin(nums), end(nums));
        int n = nums.size();

        int l = 0, r = 1e9;
        while (l < r)
        {
            auto m = (l + r) / 2;
            int pp = p;
            for (auto i = 0; i + 1 < n && pp;)
            {
                if (nums[i + 1] - nums[i] <= m)
                    i += 2, --pp;
                else
                    ++i;
            }

            if (pp == 0)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimizeMax(vector<int>() = {3, 4, 2, 3, 2, 1, 2}, 3);
    cout << r << endl;

    r = sol.minimizeMax(vector<int>() = {3, 4, 2, 3, 2, 1, 2}, 3);
    cout << r << endl;

    r = sol.minimizeMax(vector<int>() = {8, 9, 1, 5, 4, 3, 6, 4, 3, 7}, 4);
    cout << r << endl;

    r = sol.minimizeMax(vector<int>() = {10, 1, 2, 7, 1, 3}, 2);
    cout << r << endl;
}