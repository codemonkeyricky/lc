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
    TreeNode() : val(0), left(nulong longptr), right(nulong longptr) {}
    TreeNode(int x) : val(x), left(nulong longptr), right(nulong longptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nulong longptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

constexpr int mod = 1e9 + 7;
constexpr int M = 10000;
int fact[M + 1];
int inv_fact[M + 1];

inline long long multiply(long long x, long long y)
{
    return x * y % mod;
}

inline long long binexp(long long x, int pow)
{
    if (pow == 0)
        return 1;

    long long half = binexp(x, pow >> 1);
    if (pow & 1)
        return multiply(x, multiply(half, half));

    return multiply(half, half);
}

inline long long comb(int m, int n)
{
    return multiply(fact[m], multiply(inv_fact[n], inv_fact[m - n]));
}

static const auto init = []
{
    fact[0] = 1;
    for (int i = 1; i <= M; ++i)
        fact[i] = multiply(fact[i - 1], i);

    inv_fact[M] = binexp(fact[M], mod - 2);
    for (int i = M - 1; i >= 0; --i)
        inv_fact[i] = multiply(i + 1, inv_fact[i + 1]);

    return false;
}();

class Solution
{
public:
    int countGoodSubsequences(string s)
    {
        int count[26] = {0};
        for (char &c : s)
            ++count[c - 'a'];

        // Find maximal count of alphabets
        int mmax = 0;
        for (int i = 0; i < 26; ++i)
            mmax = max(mmax, count[i]);

        int rv = 0;
        for (int i = 1; i <= mmax; ++i)
        {
            long long r = 1;
            for (int j = 0; j < 26; ++j)
                if (count[j] >= i)
                    r = multiply(r, comb(count[j], i) + 1);

            rv = (rv + r - 1) % mod;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countGoodSubsequences("aabb");
    cout << r << endl;
}