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
public:
    vector<int> finalPrices(vector<int> &prices)
    {
        vector<int> stack;
        stack.push_back(-1);
        vector<int> rv(prices.size());
        for (int i = prices.size() - 1; i >= 0; i--)
        {
            int curr = prices[i];
            while (stack.back() > curr)
                stack.pop_back();
            if (stack.back() == -1)
                rv[i] = prices[i];
            else
                rv[i] = prices[i] - stack.back();
            stack.push_back(curr);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.finalPrices(vector<int>() = {8, 4, 6, 2, 3});
}