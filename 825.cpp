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
    int numFriendRequests(vector<int> &ages)
    {
        int a[121] = {}, rv = 0;
        for (auto age : ages)
            ++a[age];
        for (auto i = 15; i <= 120; ++i)
            for (int j = 0.5 * i + 8; j <= i; ++j)
                rv += a[j] * (a[i] - (i == j));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numFriendRequests(vector<int>() = {108, 115, 5, 24, 82});
    cout << r << endl;

    r = sol.numFriendRequests(vector<int>() = {16, 17, 18});
    cout << r << endl;

    r = sol.numFriendRequests(vector<int>() = {20, 30, 100, 110, 120});
    cout << r << endl;
}