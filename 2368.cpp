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
    void dfs(vector<vector<int>> &al, int k, unordered_set<int> &res, unordered_set<int> &seen)
    {
        seen.insert(k);
        for (auto &n : al[k])
            if (!seen.count(n) && !res.count(n))
                dfs(al, n, res, seen);
    }

public:
    int reachableNodes(int n, vector<vector<int>> &edges, vector<int> &restricted)
    {
        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);
        unordered_set<int> res(begin(restricted), end(restricted)), seen;
        dfs(al, 0, res, seen);
        return seen.size();
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}