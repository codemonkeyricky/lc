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
    int dfs(vector<vector<int>> &al, vector<int> &val, int k, int p, int u, int &rv)
    {
        int r = val[u];
        for (auto &v : al[u])
            if (v != p)
                r += dfs(al, val, k, u, v, rv);
        if (r % k == 0)
            r = 0, ++rv;
        return r;
    }
    
public:
    int maxKDivisibleComponents(int n, vector<vector<int>> &edges, vector<int> &values, int k)
    {
        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]),
                al[e[1]].push_back(e[0]);
        
        int rv = 0;
        dfs(al, values, k, -1, 0, rv);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}