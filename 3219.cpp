#include <iostream>
#include <vector>
#include <array>
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
    long long minimumCost(int m, int n, vector<int> &horizontalCut, vector<int> &verticalCut)
    {
        vector<array<int, 2>> sorted;
        for (auto &h : horizontalCut)
            sorted.push_back({-h, 1});

        for (auto &v : verticalCut)
            sorted.push_back({-v, 0});

        sort(begin(sorted), end(sorted));

        long long rv = 0;
        int hc = 0, vc = 0;
        for (auto [cost, is_hor] : sorted)
        {
            cost = -cost;
            if (is_hor)
                rv += (long long)cost * (vc + 1), ++hc;
            else 
                rv += (long long)cost * (hc + 1), ++vc;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumCost(2, 2, vector<int>() = {7}, vector<int>() = {4});
    cout << r << endl;

    r = sol.minimumCost(3, 2, vector<int>() = {1, 3}, vector<int>() = {5});
    cout << r << endl;
}