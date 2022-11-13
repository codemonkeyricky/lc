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
    int dfs(vector<vector<int>> &al, int k, int steps, vector<int> &seen, vector<array<int, 2>> &bob_steps)
    {
        seen[k] = true;
        bool leaf = true;
        for (auto &n : al[k])
            if (!seen[n])
                leaf = false, dfs(al, n, steps + 1, seen, bob_steps);

        seen[k] = false;
    }

public:
    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount)
    {
        int n = amount.size();

        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);

        vector<array<int, 2>> bsteps(n); ///< steps, money
        queue<array<int, 3>> q; ///< node, steps, money
        bsteps[bob] = {0, amount[bob]};
        q.push({bob, 0, amount[bob]});
        int steps = 0;
        while (q.size())
        {
            auto s = q.size();
            while (s)
            {
                auto [node, step, money] = q.front();
                q.pop();

                for (auto &n : al[node])
                    if (!bsteps[n][0] && b != bob)
                    {
                        q.push({n, steps + 1, money + amount[n]});
                        bsteps[n] = {steps + 1, money + amount[n]};
                    }

                --s;
            }

            ++steps;
        }
        
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}