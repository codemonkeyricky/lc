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
    int numPrimeArrangements(int n)
    {
        unordered_set<int> prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        int not_prime = 0, yes_prime = 0;
        for (auto i = 1; i <= n; ++i)
            if (!prime.count(i))
                ++not_prime;
            else
                ++yes_prime;

        long rv = 1;
        while (not_prime > 1)
            rv = (rv * not_prime--) % 1000000007;

        while (yes_prime > 1)
            rv = (rv * yes_prime--) % 1000000007;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numPrimeArrangements(5);
    cout << r << endl;
}