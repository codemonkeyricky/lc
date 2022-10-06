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
    long long minimumMoney(vector<vector<int>> &transactions)
    {
        vector<vector<int>> more, less;
        for (auto &t : transactions)
            if (t[0] >= t[1])
                more.push_back(t); 
            else
                less.push_back(t);
        sort(begin(more), end(more), [](const vector<int> &l, const vector<int> &r)
             { return l[1] < r[1]; });

        sort(begin(less), end(less), [](const vector<int> &l, const vector<int> &r)
             { return l[0] >= r[0]; });

        long long rv = 0, account = 0;
        for (auto &m : more)
        {
            auto cost = m[0], cash = m[1];
            account -= cost;
            if (account < 0)
                rv += abs(account), account = 0;
            account += cash;
        }

        for (auto &l : less)
        {
            auto cost = l[0], cash = l[1];
            account -= cost;
            if (account < 0)
                rv += abs(account), account = 0;
            account += cash;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.minimumMoney(vector<vector<int>>() = {{3, 9}, {7, 10}, {3, 5}, {9, 3}, {7, 4}, {3, 3}, {8, 0}});
    // cout << r << endl;

    r = sol.minimumMoney(vector<vector<int>>() = {{3, 9}, {0, 4}, {7, 10}, {3, 5}, {0, 9}, {9, 3}, {7, 4}, {0, 0}, {3, 3}, {8, 0}});
    cout << r << endl;

    r = sol.minimumMoney(vector<vector<int>>() = {{2, 1}, {5, 0}, {4, 2}});
    cout << r << endl;
}