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
    int collectTheCoins(vector<int> &coins, vector<vector<int>> &edges)
    {
        int n = coins.size();
        vector<set<int>> al(n);
        for (auto &e : edges)
            al[e[0]].insert(e[1]), al[e[1]].insert(e[0]);

        queue<int> leaf;
        for (auto i = 0; i < n; ++i)
            if (al[i].size() == 1)
                leaf.push(i);

        // Reduce to MST
        set<int> seen;
        while (leaf.size())
        {
            auto k = leaf.front();
            leaf.pop();
            if (!coins[k])
                if (al[k].size() == 1)
                {
                    auto n = *al[k].begin();
                    al[n].erase(k);
                    al[k].clear();
                    leaf.push(n);
                    seen.insert(k);
                }
        }

        leaf = queue<int>();
        for (auto i = 0; i < n; ++i)
            if (al[i].size() == 1)
                leaf.push(i);

        vector<int> coins_proxy(n);
        while (leaf.size())
        {
            auto k = leaf.front();
            leaf.pop();

            if (coins_proxy[k] < 2 && al[k].size() == 1)
            {
                // does not hold a coin
                // trim and add all neighbors to be considered
                for (auto &n : al[k])
                    if (!seen.count(n))
                    {
                        if (coins[k])
                            coins_proxy[n] = max(coins_proxy[n], 1);

                        if (coins_proxy[k])
                            coins_proxy[n] = max(coins_proxy[k] + 1, coins_proxy[n]);

                        leaf.push(n);

                        al[n].erase(k);
                    }

                seen.insert(k);
            }
        }

        if (seen.size() == n)
            return 0;

        return ((n - seen.size()) - 1) * 2;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.collectTheCoins(vector<int>() = {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1}, vector<vector<int>>() = {{0, 1}, {1, 2}, {2, 3}, {1, 4}, {4, 5}, {5, 6}, {6, 7}, {3, 8}, {6, 9}, {7, 10}, {10, 11}, {10, 12}, {7, 13}, {12, 14}, {13, 15}, {14, 16}, {15, 17}, {10, 18}});
    cout << r << endl;

    r = sol.collectTheCoins(vector<int>() = {1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0}, vector<vector<int>>() = {{0, 1}, {1, 2}, {1, 3}, {2, 4}, {4, 5}, {5, 6}, {5, 7}, {4, 8}, {7, 9}, {7, 10}, {10, 11}});
    cout << r << endl;

    r = sol.collectTheCoins(vector<int>() = {0, 0}, vector<vector<int>>() = {{0, 1}});
    cout << r << endl;

    r = sol.collectTheCoins(vector<int>() = {1, 0, 0, 0, 0, 1}, vector<vector<int>>() = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}});
    cout << r << endl;
}