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
    int find(int k)
    {
        if (parent[k] < 0)
            return k;
        return find(parent[k]);
    }

    vector<int> parent;

public:
    int minScore(int n, vector<vector<int>> &roads)
    {
        parent = vector<int>(n + 1, -1);
        for (auto &r : roads)
        {
            auto p1 = find(r[0]);
            auto p2 = find(r[1]);
            if (p1 != p2)
            {
                if (parent[p1] > parent[p2])
                    swap(p1, p2);
                parent[p1] += parent[p2];
                parent[p2] = p1;
            }
        }

        int rv = 1e9;
        for (auto &r : roads)
            if (find(1) == find(r[0]))
                rv = min(rv, r[2]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minScore(4, vector<vector<int>>() = {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}});
    cout << r << endl;
}