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
    int makeTheIntegerZero(long n1, long n2)
    {
        for (auto k = 0; k <= 60; ++k)
        {
            long v = n1 - k * n2;
            if (v >= 0)
            {
                auto bits = __builtin_popcountll(v);
                auto kk = k;
                if (kk >= bits)
                {
                    while (v && kk)
                        v >>= 1, --kk;
                    if (kk == 0)
                        return k;
                }
            }
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.makeTheIntegerZero(85, 42);
    cout << r << endl;

    r = sol.makeTheIntegerZero(112577768, -501662198);
    cout << r << endl;

    r = sol.makeTheIntegerZero(110, 55);
    cout << r << endl;

    r = sol.makeTheIntegerZero(5, -21);
    cout << r << endl;

    r = sol.makeTheIntegerZero(5, 7);
    cout << r << endl;

    r = sol.makeTheIntegerZero(3, -2);
    cout << r << endl;
}