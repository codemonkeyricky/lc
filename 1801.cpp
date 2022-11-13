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
    int getNumberOfBacklogOrders(vector<vector<int>> &orders)
    {
        priority_queue<array<int,2>> buy;
        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> sell;
        for (auto &order : orders)
        {
            auto price = order[0];
            auto amount = order[1];
            auto isSell = order[2];
            if (isSell)
            {
                while (amount && buy.size() && price <= buy.top()[0])
                {
                    auto top = buy.top();
                    buy.pop();
                    auto b = min(amount, top[1]);
                    amount -= b;
                    if (top[1] -= b)
                        buy.push(top);
                }
                if (amount)
                    sell.push({price, amount});
            }
            else
            {
                while (amount && sell.size() && price >= sell.top()[0])
                {
                    auto top = sell.top();
                    sell.pop();
                    auto b = min(amount, top[1]);
                    amount -= b;
                    if (top[1] -= b)
                        sell.push(top);
                }
                if (amount)
                    buy.push({price, amount});
            }
        }

        int rv = 0;
        while (buy.size())
            rv = (rv + buy.top()[1]) % 1000000007, buy.pop();
        while (sell.size())
            rv = (rv + sell.top()[1]) % 1000000007, sell.pop();
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.getNumberOfBacklogOrders(vector<vector<int>>() = {{19, 28, 0}, {9, 4, 1}, {25, 15, 1}});
    cout << r << endl;

    r = sol.getNumberOfBacklogOrders(vector<vector<int>>() = {{7, 1000000000, 1}, {15, 3, 0}, {5, 999999995, 0}, {5, 1, 1}});
    cout << r << endl;
}