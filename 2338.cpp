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

const int N = 10020;
static long long fact[N]; // , factInv[N];
bool __precompute__ = []()
{
    fact[0] = fact[1] = 1;
    for (int i = 2; i < N; ++i)
        fact[i] = (fact[i - 1] * i) % 1000000007;

    return 0;
}();

class Solution
{
    int static constexpr mod = 1000000007;
    int modPow(int x, unsigned int y, unsigned int m)
    {
        if (y == 0)
            return 1;
        long p = modPow(x, y / 2, m) % m;
        p = (p * p) % m;
        return y % 2 ? (p * x) % m : p;
    }

    int inv(int a, int p)
    {
        return modPow(a, p - 2, p);
    }

    long long comb(int n, int r)
    {
        return fact[n] * inv(fact[r], mod) % mod * inv(fact[n - r], mod) % mod;
    }

public:
    int idealArrays(int n, int mv)
    {
        long long rv = 0;
        for (int i = 1; i <= mv; ++i)
        {
            int x = i;
            unordered_map<int, int> mp;

            /*
             *  Prime factorization
             */

            for (int j = 2; j * j <= mv; ++j)
                while (x % j == 0)
                    mp[j] += 1, x /= j;

            if (x > 1)
                mp[x] += 1;

            long long r = 1;
            for (auto [k, v] : mp)
                (r *= comb(n + v - 1, v)) %= mod; 

            (rv += r) %= mod;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.idealArrays(3, 10);
    cout << r << endl;

    r = sol.idealArrays(5, 3);
    cout << r << endl;

    r = sol.idealArrays(2, 5);
    cout << r << endl;
}