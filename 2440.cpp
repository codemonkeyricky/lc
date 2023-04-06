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

using v = vector<int>;
using vv = vector<vector<int>>;
class Solution
{
    bool dfs(v &nums, vv &al, int k, int sum, v &seen, queue<int> &q, int &rv)
    {
        if (sum - nums[k] < 0)
            return false;

        if (sum - nums[k] == 0)
        {
            seen[k] = true;
            for (auto &n : al[k])
                if (!seen[n])
                    q.push(n), ++rv;
            return true;
        }

        sum -= nums[k];

        for (auto &n : al[k])
            if (!seen[n])
            {
                seen[n] = true;
                int r = 0;
                r = dfs(nums, al, n, sum, seen, q, rv);
                if (r)
                    return true;
            }

        return false;
    }

public:
    int componentValue(v &nums, vv &edges)
    {
        int n = nums.size();
        vv al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);
        
        auto s = -1;
        queue<int> corners;
        for (auto i = 0; i < n && s == -1; ++i)
            if (al[i].size() == 1)
                corners.push(i);

        auto sum = accumulate(begin(nums), end(nums), 0);
        for (int split = n, valid = true; split >= 1; --split, valid = true)
            if (sum % split == 0)
            {
                int rv = 0;
                auto q = corners;
                v seen(n);
                while (q.size() && valid)
                {
                    auto k = q.front();
                    q.pop();
                    if (!seen[k])
                    {
                        seen[k] = true;
                        if (!dfs(nums, al, k, sum / split, seen, q, rv))
                            valid = false;
                    }
                }
                if (valid)
                    return rv;
            }

        return 0;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.componentValue(v() = {1, 2, 1, 1, 1}, vv() = {{0, 1}, {1, 3}, {3, 4}, {4, 2}});
    cout << r << endl;

    r = sol.componentValue(v() = {6, 2, 2, 2, 6}, vv() = {{0, 1}, {1, 2}, {1, 3}, {3, 4}});
    cout << r << endl;

    r = sol.componentValue(v() = {2}, vv() = {});
    cout << r << endl;
}