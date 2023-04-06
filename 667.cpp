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
    vector<int> constructArray(int n, int k)
    {
        vector<int> rv, copy;
        for (auto i = 1; i <= n; ++i)
        {
            rv.push_back(i);
            if (i <= k + 1)
                copy.push_back(i);
        }

        for (auto i = 0, j = k, l = 0; i <= j; l += 2)
        {
            rv[l] = copy[i++];
            if (l < k)
                rv[l + 1] = copy[j--];
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.constructArray(10, 5);
    cout << r << endl;
}