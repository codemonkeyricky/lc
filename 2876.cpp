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
    vector<int> loop, cnt, seen, depth;
    array<int, 2> dfs(vector<int> &edges, int k, int d) 
    {
        // never visited
        if (seen[k] == 0)
        {
            seen[k] = 1;
            depth[k] = d;
            auto [dd, c] = dfs(edges, edges[k], d + 1);
            if (dd <= d)
                loop[k] = c;
            depth[k] = 0;
            seen[k] = 2;
            return {dd, c};
        }
        // loop
        else if (seen[k] == 1)
            return {depth[k], d - depth[k]};

        return {0, 0};
    }

    int dfs2(vector<int> &edges, int k)
    {
        if (loop[k])
            return loop[k];

        if (seen[k] == 0)
        {
            cnt[k] = 1 + dfs2(edges, edges[k]);
            seen[k] = 1;
        }

        return cnt[k];
    }

public:
    vector<int> countVisitedNodes(vector<int> &edges)
    {
        int n = edges.size();
        loop = depth = seen = vector<int>(n);
        for (auto i = 0; i < n; ++i)
            dfs(edges, i, 0);

        cnt = loop;
        depth = seen = vector<int>(n);
        for (auto i = 0; i < n; ++i)
            dfs2(edges, i);

        return cnt;
    }
};

int main()
{
    Solution sol;
    vector<int> r; 

    r = sol.countVisitedNodes(vector<int>() = {1, 2, 0, 0});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}