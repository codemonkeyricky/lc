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

vector<int> isPrime, primes; 
class Solution
{
public:
    vector<vector<int>> findPrimePairs(int n)
    {
        if (isPrime.empty())
        {
            isPrime = vector<int>(1000001, 1);
            for (auto i = 2; i * i < isPrime.size(); ++i)
                for (auto k = 2; k * i < isPrime.size(); ++k)
                    isPrime[i * k] = 0;
            for (auto i = 2; i < isPrime.size(); ++i)
                if (isPrime[i])
                    primes.push_back(i);
        }

        vector<vector<int>> rv;
        auto k = lower_bound(begin(primes), end(primes), n) - begin(primes);
        for (auto i = 0; i < primes.size() && primes[i] <= n / 2; ++i)
        {
            auto it = lower_bound(begin(primes), end(primes), n - primes[i]);
            if (it != end(primes) && *it == n - primes[i])
                rv.push_back({primes[i], n - primes[i]});
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.findPrimePairs(4);
    sol.findPrimePairs(10);
}