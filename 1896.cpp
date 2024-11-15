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
#define OR 1
#define AND 0

    array<int, 2> resolve(array<int, 2> left, int op, array<int, 2> right)
    {
        array<int, 2> rv;
        if (op) // or
        {
            rv[0] = min(1 + min(left[0], right[0]), left[0] + right[0]);
            rv[1] = min(left[1], right[1]);
        }
        else // and
        {
            rv[0] = min(left[0], right[0]);
            rv[1] = min(1 + min(left[1], right[1]), left[1] + right[1]);
        }
        return rv;
    }

    array<int, 2> dfs(string &expr, int &k)
    {
        array<int, 2> cost = {};
        int op = -1;
        for (auto i = k; i < expr.size(); ++i)
            if (expr[i] == '(')
            {
                ++i;
                auto rv = dfs(expr, i);
                if (op == -1)
                    cost = rv;
                else
                    cost = resolve(cost, op, rv);
            }
            else if (expr[i] == ')')
            {
                k = i;
                return cost;
            }
            else if (expr[i] == '&')
                op = AND; 
            else if (expr[i] == '|')
                op = OR;
            else if (expr[i] == '1')
            {
                if (op == -1)
                    ++cost[0];
                else
                    cost = resolve(cost, op, {1, 0});
            }
            else if (expr[i] == '0')
            {
                if (op == -1) // first number
                    ++cost[1];
                else
                    cost = resolve(cost, op, {0, 1});
            }
        return cost; 
    }

public:
    int minOperationsToFlip(string expression)
    {
        int k = 0;
        auto rv = dfs(expression, k);
        return max(rv[0], rv[1]);
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.minOperationsToFlip("1&0|(0&0)&0|0&(1&(1))");
    // cout << r << endl;

    // r = sol.minOperationsToFlip("(0|(1|0&1))");
    // cout << r << endl;

    r = sol.minOperationsToFlip("(0&0)&(0&0&0)");
    cout << r << endl;

    r = sol.minOperationsToFlip("1&(0|1)");
    cout << r << endl;
}