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
    bool containsPattern(vector<int> &a, int m, int k, int cnt = 0)
    {
        for (int i = 0; i + m < a.size() && cnt < m * (k - 1); ++i)
            cnt = a[i] == a[i + m] ? cnt + 1 : 0;
        return cnt == m * (k - 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.containsPattern(vector<int>() = {0, 2, 4, 1, 2, 3, 1, 2, 3}, 3, 2);
    cout << r << endl;

    r = sol.containsPattern(vector<int>() = {1, 2, 2, 2, 1, 1, 2, 2, 2}, 1, 3);
    cout << r << endl;

    r = sol.containsPattern(vector<int>() = {4, 4, 4, 4}, 1, 3);
    cout << r << endl;
}