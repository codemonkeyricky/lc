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
    bool canMirror(int i, int j, int l, int n)
    {
        if (i > j)
            swap(i, j);

        if (j - i >= l)
            return false;

        if (l % 2 == 0)
        {
            // if k is even, i and j must be odd/even
            if ((i % 2) ^ (j % 2) == 0)
                return false;
        }
        else 
        {
            // if k is odd, then i and j must be both odd or even
            if ((i % 2) ^ (j % 2) == 1)
                return false;
        }

        auto d = j - i + 1;
        auto left = l - d;
        if (i - left / 2 < 0)
            return false;

        if (j + left / 2 >=n )
            return false;

        return true;
    }

public:
    vector<int> minReverseOperations(int n, int p, vector<int> &banned, int k)
    {
        set<int> ban(begin(banned), end(banned));
        set<int> free[2];
        for (auto i = 0; i < n; ++i)
            if (i != p && !ban.count(i))
                free[i & 1].insert(i);

        vector<int> rv(n, -1);
        queue<array<int, 2>> q;
        q.push({p, 0});
        rv[p] = 0;
        while (q.size())
        {
            auto [p, op] = q.front();
            q.pop();

            int o = (k % 2 == 0) ? (1 - p & 1) : (p & 1);
            auto it = free[o].lower_bound(p - k + 1);
            while (it != end(free[o]) && *it - p < k)
            {
                // if (canMirror(*it, p, k, n))
                {
                    q.push({*it, op + 1}), rv[*it] = op + 1;
                    free[o].erase(it++);
                }
                // else
                //     it++;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.minReverseOperations(5, 0, vector<int>() = {}, 2);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.minReverseOperations(5, 0, vector<int>() = {}, 4);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.minReverseOperations(8, 6, vector<int>() = {0}, 5);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.minReverseOperations(5, 0, vector<int>() = {2, 4}, 3);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.minReverseOperations(4, 0, vector<int>() = {1, 2}, 4);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.minReverseOperations(4, 2, vector<int>() = {0, 1, 3}, 1);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}