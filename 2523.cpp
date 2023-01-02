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
    vector<int> closestPrimes(int left, int right)
    {
        int k = left;
        vector<int> is_prime(right + 1, 1);
        for (auto i = 2; i * i <= right; ++i)
        {
            int k = i + i;
            while (k <= right)
                is_prime[k] = false, k += i;
        }

        vector<int> prime;
        for (auto i = max(left, 2); i <= right; ++i)
            if (is_prime[i])
                prime.push_back(i);
        
        vector<int> rv; 
        int gap = 1e9;
        for (auto i = 1; i < prime.size(); ++i)
            if (prime[i] - prime[i - 1] < gap)
                rv = {prime[i - 1], prime[i]}, gap = prime[i] - prime[i - 1];

        if (rv.size() == 2)
            return rv;
        return {-1, -1};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.closestPrimes(1, 1000000);

    sol.closestPrimes(10, 19);
}