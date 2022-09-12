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
    int modPow(int x, unsigned int y, unsigned int m)
    {
        if (y == 0)
            return 1;
        long p = modPow(x, y / 2, m) % m;
        p = (p * p) % m;
        return y % 2 ? (p * x) % m : p;
    }

public:
    int maxNiceDivisors(int pf)
    {
        if (pf <= 3)
            return pf;

        int MOD = 1e9 + 7;

        int threes = pf / 3, twos = 0;
        if (pf % 3 == 0)
            ;
        else if (pf % 3 == 2)
            twos = 1;
        else if (pf % 3 == 1)
            --threes, twos = 2;

        long long rv = modPow(3, threes, MOD);
        while (twos--)
            rv = (rv * 2) % MOD;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}