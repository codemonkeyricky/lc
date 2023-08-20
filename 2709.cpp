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
    void unionize(int i, int j)
    {
        auto p1 = find(i);
        auto p2 = find(j);
        if (p1 != p2)
        {
            if (parent[p2] < parent[p1])
                swap(p1, p2);
            parent[p1] += parent[p2];
            parent[p2] = p1;
        }
    }

    int find(int k)
    {
        if (parent[k] < 0)
            return k;
        return parent[k] = find(parent[k]);
    }

    vector<int> parent;

public:
    bool canTraverseAllPairs(vector<int> &nums)
    {
        if (accumulate(begin(nums), end(nums), 0ll) == 1)
            return true;

        if (accumulate(begin(nums), end(nums), 0ll) == nums.size())
            return false;

        int n = nums.size();
        sort(begin(nums), end(nums));
        vector<int> lookup(nums.back() + 1, -1); // num to index
        parent = vector<int>(n, -1);
        for (auto i = 0; i < n; ++i)
        {
            if (lookup[nums[i]] != -1)
                unionize(lookup[nums[i]], i);
            else
                lookup[nums[i]] = i;
        }

        for (auto i = 2; i <= nums.back(); ++i)
        {
            int anchor = -1;
            for (auto j = 1; i * j <= nums.back(); ++j)
                if (lookup[i * j] != -1)
                {
                    if (anchor == -1)
                        anchor = i * j;
                    unionize(lookup[anchor], lookup[i * j]);
                }
        }

        set<int> uniq;
        for (auto i = 1; i <= nums.back(); ++i)
            if (lookup[i] != -1)
                uniq.insert(find(lookup[i]));

        return uniq.size() == 1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.canTraverseAllPairs(vector<int>() = {1, 1});
    cout << r << endl;

    r = sol.canTraverseAllPairs(vector<int>() = {4, 3, 12, 8});
    cout << r << endl;

    r = sol.canTraverseAllPairs(vector<int>() = {3, 9, 5});
    cout << r << endl;

    r = sol.canTraverseAllPairs(vector<int>() = {20, 6});
    cout << r << endl;

    r = sol.canTraverseAllPairs(vector<int>() = {2, 3, 6});
    cout << r << endl;
}