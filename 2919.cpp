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
    long long minIncrementOperations(vector<int> &A, int k)
    {
        long long p3 = 0, p2 = 0, p1 = 0, p0;
        for (int &a : A)
        {
            p0 = min({p3, p2, p1}) + max(k - a, 0);
            p3 = p2;
            p2 = p1;
            p1 = p0;
        }
        return min({p1, p2, p3});
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minIncrementOperations(vector<int>() = {42, 19, 52, 36, 8, 5, 9}, 656);
    cout << r << endl;

    r = sol.minIncrementOperations(vector<int>() = {43, 31, 14, 4}, 73);
    cout << r << endl;

    r = sol.minIncrementOperations(vector<int>() = {2, 3, 0, 0, 2}, 4);
    cout << r << endl;
}