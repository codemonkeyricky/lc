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
    int maximumXorProduct(long long a, long long b, int n)
    {
        long long x = 0;
        long long aaa = a & ~((1ll << n) - 1);
        long long bbb = b & ~((1ll << n) - 1);
        for (long long i = n - 1; i >= 0; --i)
        {
            long long mask = 1ll << i;
            long long aa = a & mask; 
            long long bb = b & mask; 
            if (aa == bb)
                if (aa) // both are set
                    ; // do nothing
                else // both are clear
                    x |= mask, aaa |= mask, bbb |= mask; // set x so a and b both get get this
            else // aa != bb
                if (aa) // only aa is set
                {
                    if (bbb < aaa)
                        bbb |= mask, x |= mask; /// b gets the mask
                    else 
                        aaa |= mask;
                }
                else // only bb is set
                {
                    if (aaa < bbb)
                        aaa |= mask, x |= mask; /// a gets the mask
                    else 
                        bbb |= mask;
                }
        }

        __int128 aa = a, bb = b, xx = x;

        return ((aa ^ xx) * (bb ^ xx)) % 1000000007;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumXorProduct(0, 3, 1);
    cout << r << endl;

    r = sol.maximumXorProduct(1, 6, 3);
    cout << r << endl;

    r = sol.maximumXorProduct(6, 7, 5);
    cout << r << endl;

    r = sol.maximumXorProduct(12, 5, 4);
    cout << r << endl;
}