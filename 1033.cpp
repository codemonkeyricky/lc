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
    int fast(int a, int b, int c)
    {
        if (a + 1 == b || b + 1 == c || a + 2 == b || b + 2 == c)
            return 1;
        return 2;
    }

    int slow(int a, int b, int c)
    {
        return c - b - 1 + b - a - 1;
    }

public:
    vector<int> numMovesStones(int a, int b, int c)
    {
        if (a > b)
            swap(a, b);
        if (b > c)
            swap(b, c);
        if (a > b)
            swap(a, b);

        if (a + 1 == b && b + 1 == c)
            return {0, 0};
        return {fast(a, b, c), slow(a, b, c)};
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}