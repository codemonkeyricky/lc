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
    int waysToMakeFair(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> le(n), lo(n), re(n), ro(n);
        for (auto i = 0; i < n; ++i)
            if (i % 2)
            {
                lo[i] = nums[i] + (i >= 2 ? lo[i - 2] : 0);
                le[i] = le[i - 1];
            }
            else
            {
                le[i] = nums[i] + (i >= 2 ? le[i - 2] : 0);
                lo[i] = i ? lo[i - 1] : 0;
            }

        for (int i = n - 1; i >= 0; --i)
            if (i % 2)
            {
                ro[i] = nums[i] + (i < n - 2 ? ro[i + 2] : 0);
                re[i] = i < n - 1 ? re[i + 1] : 0;
            }
            else
            {
                re[i] = nums[i] + (i < n - 2 ? re[i + 2] : 0);
                ro[i] = i < n - 1 ? ro[i + 1] : 0;
            }

        int rv = 0;
        for (auto i = 0; i < n; ++i)
            if (i % 2)
            {
                if ((i ? lo[i - 1] : 0) + (i < n - 1 ? re[i + 1] : 0)
                 == (i ? le[i - 1] : 0) + (i < n - 1 ? ro[i + 1] : 0))
                    ++rv;
            }
            else 
                if ((i ? le[i - 1] : 0) + (i < n - 1 ? ro[i + 1] : 0)
                 == (i ? lo[i - 1] : 0) + (i < n - 1 ? re[i + 1] : 0))
                    ++rv;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.waysToMakeFair(vector<int>() = {1, 1, 1, 1, 1});
    cout << r << endl;

    r = sol.waysToMakeFair(vector<int>() = {1, 1, 1});
    cout << r << endl;

    r = sol.waysToMakeFair(vector<int>() = {2, 1, 6, 4});
    cout << r << endl;
}