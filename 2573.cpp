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
    string findTheString(vector<vector<int>> &lcp)
    {
        int n = lcp.size();
        string cand(n, 'a');

        for (auto i = 0; i < n; ++i)
            for (auto j = i; j < n; ++j)
                if (lcp[i][j] == 0 && cand[i] == cand[j])
                    ++cand[j];

        for (auto &c : cand)
            if (c > 'z')
                return "";

        vector<vector<int>> lcp2(n + 1, vector<int>(n + 1));
        for (int i = n - 1; i >= 0; --i)
            for (int j = n - 1; j >= 0; --j)
                if (cand[i] == cand[j])
                    lcp2[i][j] = 1 + lcp2[i + 1][j + 1];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (lcp[i][j] != lcp2[i][j])
                    return "";

        return cand;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.findTheString(vector<vector<int>>() = {
                              {6, 0, 0, 3, 0, 0},
                              {0, 5, 0, 0, 2, 0},
                              {0, 0, 4, 0, 0, 1},
                              {3, 0, 0, 3, 0, 0},
                              {0, 2, 0, 0, 2, 0},
                              {0, 0, 1, 0, 0, 1}});
    cout << r << endl;

    r = sol.findTheString(vector<vector<int>>() = {{4, 3, 2, 1}, {3, 3, 2, 1}, {2, 2, 2, 1}, {1, 1, 1, 3}});
    cout << r << endl;

    r = sol.findTheString(vector<vector<int>>() = {{4, 0, 2, 0}, {0, 3, 0, 1}, {2, 0, 2, 0}, {0, 1, 0, 1}});
    cout << r << endl;
}