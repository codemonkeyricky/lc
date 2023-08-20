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
    int diagonalPrime(vector<vector<int>> &nums)
    {
        set<int> diag; 
        int n = nums.size();
        for (auto i = 0; i < n; ++i)
            diag.insert(nums[i][i]), diag.insert(nums[n - i - 1][i]);

        vector<int> prime(*prev(diag.end()) + 1, 1);
        for (auto i = 2; i * i < prime.size(); i++)
            for (auto j = 2; i * j < prime.size(); ++j)
                prime[i * j] = 0;

        int rv = 0;
        for (auto &v : diag)
            if (prime[v])
                rv = v;
        
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.diagonalPrime(vector<vector<int>>() = {{11, 119}, {914, 371}});
    cout << r << endl;

    r = sol.diagonalPrime(vector<vector<int>>() = {{1, 2, 3}, {5, 6, 7}, {9, 10, 11}});
    cout << r << endl;
}