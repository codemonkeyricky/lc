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
    int minOperationsMaxProfit(vector<int> &customers, int boarding, int running)
    {
        int profit = 0;
        int n = customers.size();
        int gondola[4] = {}, k = 0;
        int maxProfit = 0;
        int rotation = -1;
        for (auto i = 0, waiting = 0, rot = 1; i < n || waiting; ++i, ++rot)
        {
            if (i < n)
                waiting += customers[i];
            gondola[k] = 0;
            int b = min(4, waiting);
            waiting -= b;
            profit += b * boarding - running;
            if (profit > maxProfit)
                maxProfit = profit, rotation = rot;
            k = (k + 1) % 4;
        }
        return rotation; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperationsMaxProfit(vector<int>() = {8, 3}, 5, 6);
    cout << r << endl;
}