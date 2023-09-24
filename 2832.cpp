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
            if (p2 < p1)
                swap(p1, p2);
            parent[p1] += parent[p2];
            parent[p2] = p1;
        }
    }

    int find(int k)
    {
        if (parent[k] < 0)
            return k;
        return find(parent[k]);
    }

    vector<int> parent;

public:
    vector<int> maximumLengthOfRanges(vector<int> &nums)
    {
        int n = nums.size();
        priority_queue<array<int, 2>> q;
        for (auto i = 0; i < n; ++i)
            q.push({-nums[i], i});

        vector<int> rv(n);
        parent = vector<int>(n, -1);
        vector<int> seen(n);
        while (q.size())
        {
            auto [v, k] = q.top();
            q.pop();
            seen[k] = true;
            if (k && seen[k - 1])
                unionize(k - 1, k);
            if (k + 1 < n && seen[k + 1])
                unionize(k, k + 1);

            rv[k] = -parent[find(k)];
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.maximumLengthOfRanges(vector<int>() = {1, 5, 4, 3, 6});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}