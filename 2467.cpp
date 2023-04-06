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
    int alice_dfs(vector<vector<int>> &al, vector<int> &amount, int k, int steps, int money, vector<int> &seen, vector<array<int, 2>> &bob_steps)
    {
        seen[k] = true;

        if (bob_steps[k][0] == 0 || steps < bob_steps[k][0])
            money += amount[k];
        else if (bob_steps[k][0] == steps)
            money += amount[k] / 2;

        bool leaf = true;
        int rv = -1e9;
        for (auto &n : al[k])
            if (!seen[n])
                leaf = false, rv = max(rv, alice_dfs(al, amount, n, steps + 1, money, seen, bob_steps));

        if (leaf)
            rv = max(rv, money);

        seen[k] = false;

        return rv;
    }

    bool bob_dfs(vector<vector<int>> &al, vector<int> &amount, int k, int steps, int money, vector<array<int, 2>> &bob_steps)
    {
        bob_steps[k] = {steps, money + amount[k]};
        if (k == 0)
            return true;
        for (auto &n : al[k])
            if (!bob_steps[n][0])
                if (bob_dfs(al, amount, n, steps + 1, money + amount[k], bob_steps))
                    return true;
        bob_steps[k] = {};
        return false;
    }

public:
    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount)
    {
        int n = amount.size();

        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);

        vector<array<int, 2>> bsteps(n); ///< steps, money
        bob_dfs(al, amount, bob, 1, 0, bsteps);

        vector<int> seen(n);
        return alice_dfs(al, amount, 0, 1, 0, seen, bsteps);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.mostProfitablePath(vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {3, 4}}, 3, vector<int>() = {-2, 4, 2, -4, 6});
    cout << r << endl;
}