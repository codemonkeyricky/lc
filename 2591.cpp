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
    int dfs(int money, int children)
    {
        if (money == 3)
            return -1;

        if (money <= 0)
            return 0;

        if (money < 7)
            return 0;

        if (children == 1)
            return money == 7;

        auto r = dfs(money - 7, children - 1);
        if (r < 0)
            return dfs(money - 6, children - 1);
        return r + 1;
    }

public:
    int distMoney(int money, int children)
    {
        if (money < children)
            return -1;
        
        money -= children;
        auto rv = dfs(money, children);
        return rv < 0 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.distMoney(3, 2);
    cout << r << endl;

    r = sol.distMoney(20, 3);
    cout << r << endl;
}