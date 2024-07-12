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
    typedef long long ll;
    static constexpr int mod = 1e9 + 7;
    static constexpr int M = 100001;
    int fact[M + 1];
    int inv_fact[M + 1];

    inline ll multiply(ll x, ll y)
    {
        return x * y % mod;
    }

    inline ll binexp(ll x, int pow)
    {
        if (pow == 0)
        {
            return 1;
        }
        ll half = binexp(x, pow >> 1);
        if (pow & 1)
        {
            return multiply(x, multiply(half, half));
        }
        return multiply(half, half);
    }

    inline ll comb(int m, int n)
    {
        return multiply(fact[m], multiply(inv_fact[n], inv_fact[m - n])) % mod;
    }

    int init()
    {
        fact[0] = 1;
        for (int i = 1; i <= M; ++i)
            fact[i] = multiply(fact[i - 1], i);

        inv_fact[M] = binexp(fact[M], mod - 2);
        for (int i = M - 1; i >= 0; --i)
            inv_fact[i] = multiply(i + 1, inv_fact[i + 1]);

        return false;
    }

    int twoPow(int k)
    {
        int rv = 1;
        while (k--)
            rv = (rv * 2) % mod;
        return rv;
    }

public:
    int numberOfSequence(int n, vector<int> &sick)
    {
        init();

        vector<int> gap_size, gap_ways;
        int i;
        for (i = 1; i < sick.size(); ++i)
            if (sick[i] - sick[i - 1] > 1)
            {
                gap_size.push_back(sick[i] - sick[i - 1] - 1);
                gap_ways.push_back(twoPow(gap_size.back() - 1));
            }

        if (n - sick.back() > 1)
        {
            gap_size.push_back(n - sick.back() - 1);
            gap_ways.push_back(1);
        }

        long rv = 1;
        int nn = n - sick.size();
        for (auto i = 0; i < gap_size.size(); ++i)
        {
            rv = (rv * comb(nn, gap_size[i])) % mod;
            rv = (rv * gap_ways[i]) % mod;
            nn -= gap_size[i];
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfSequence(101, vector<int>() = {40, 48, 56, 83, 90});
    cout << r << endl;

    r = sol.numberOfSequence(4, vector<int>() = {1});
    cout << r << endl;

    r = sol.numberOfSequence(5, vector<int>() = {0, 4});
    cout << r << endl;
}