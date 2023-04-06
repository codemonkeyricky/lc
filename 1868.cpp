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
    vector<vector<int>> findRLEArray(vector<vector<int>> &enc1, vector<vector<int>> &enc2)
    {
        vector<vector<int>> chunks;
        for (auto i = 0, j = 0; i < enc1.size() && j < enc2.size();)
        {
            int v1 = enc1[i][0], l1 = enc1[i][1];
            int v2 = enc2[j][0], l2 = enc2[j][1];
            if (l1 < l2)
                chunks.push_back({v1 * v2, l1}), enc2[j][1] = l2 - l1, ++i;
            else if (l2 < l1)
                chunks.push_back({v1 * v2, l2}), enc1[i][1] = l1 - l2, ++j;
            else
                chunks.push_back({v1 * v2, l2}), ++i, ++j;
        }

        vector<vector<int>> rv;
        for (auto &c : chunks)
            if (rv.empty() || rv.back()[0] != c[0])
                rv.push_back(c);
            else
                rv.back()[1] += c[1];
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findRLEArray(vector<vector<int>>() = {{2, 2}, {5, 5}, {1, 5}, {2, 5}, {4, 2}, {5, 3}, {1, 2}, {4, 3}, {3, 2}, {2, 3}}, vector<vector<int>>() = {{1, 1}, {4, 1}, {3, 3}, {5, 3}, {1, 4}, {5, 1}, {4, 1}, {5, 3}, {3, 5}, {2, 1}, {1, 2}, {3, 1}, {2, 1}, {4, 3}, {3, 1}, {2, 1}});
    sol.findRLEArray(vector<vector<int>>() = {{1, 3}, {2, 3}}, vector<vector<int>>() = {{6, 3}, {3, 3}});
}