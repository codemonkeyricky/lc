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
    int MOD = 1000000007;
    long superPow(int n, int p)
    {
        if (p == 0)
            return 0;

        if (p == 1)
            return n;

        long rr = superPow(n, p / 2);
        long rv = rr * rr % MOD;
        if (p % 2)
            rv = rv * n % MOD;
        return rv;
    }

public:
    int monkeyMove(int n)
    {
        auto rv = superPow(2, n) - 2;
        if (rv < 0)
            rv += MOD;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}