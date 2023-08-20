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
    long long findMaximumElegance(vector<vector<int>> &items, int k)
    {
        int n = items.size();
        sort(begin(items), end(items), greater<vector<int>>());

        long long rv = 0, profit = 0;
        map<int, multiset<int>> cat;
        multiset<array<int, 2>> to_replace; 
        for (auto i = 0; i < n; ++i)
        {
            auto p = items[i][0], c = items[i][1];
            if (i < k)
            {
                profit += p;
                cat[c].insert(p);
                if (cat[c].size() > 1)
                    to_replace.insert({p, c});
            }
            else 
            {
                if (!cat.count(c))
                {
                    if (to_replace.size())
                    {
                        auto [pp, cc] = *to_replace.begin();
                        auto b = profit - pp + p + (long long)((cat.size() + 1) * (cat.size() + 1));
                        cat[c].insert(p);
                        profit = profit - pp + p;
                        to_replace.erase(to_replace.begin());
                        cat[cc].erase(cat[cc].find(pp));
                    }
                }
            }

            rv = max(rv, profit + (long long)(cat.size() * cat.size()));
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findMaximumElegance(vector<vector<int>>() = {{7, 1}, {4, 1}, {3, 2}, {10, 1}}, 3);
    cout << r << endl;

    r = sol.findMaximumElegance(vector<vector<int>>() = {{2, 2}, {8, 6}, {10, 6}, {2, 4}, {9, 5}, {4, 5}}, 4);
    cout << r << endl;

    r = sol.findMaximumElegance(vector<vector<int>>() = {{1, 1}, {8, 2}}, 2);
    cout << r << endl;

    r = sol.findMaximumElegance(vector<vector<int>>() = {{1, 1}, {2, 1}, {3, 1}}, 3);
    cout << r << endl;

    r = sol.findMaximumElegance(vector<vector<int>>() = {{3, 1}, {3, 1}, {2, 2}, {5, 3}}, 3);
    cout << r << endl;

    r = sol.findMaximumElegance(vector<vector<int>>() = {{3, 2}, {5, 1}, {10, 1}}, 2);
    cout << r << endl;
}