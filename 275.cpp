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
    int hIndex(vector<int> &citations)
    {
        int n = citations.size();
        int l = 0;
        int r = n;
        while (l < r)
        {
            int m = (l + r) / 2;
            if (citations[m] < n - m)
                l = m + 1;
            else
                r = m;
        }
        return n - l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.hIndex(vector<int>() = {0});
    cout << r << endl;

    // r = sol.hIndex(vector<int>() = {11, 15});
    // cout << r << endl;

    // r = sol.hIndex(vector<int>() = {1, 2});
    // cout << r << endl;

    // r = sol.hIndex(vector<int>() = {100});
    // cout << r << endl;

    // r = sol.hIndex(vector<int>() = {1, 2, 100});
    // cout << r << endl;

    r = sol.hIndex(vector<int>() = {0, 1, 3, 5, 6});
    cout << r << endl;
}