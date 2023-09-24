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
    long long maximumSum(vector<int> &nums)
    {
        long long n = nums.size();
        vector<long long> sq;
        sq.push_back(1);
        long long curr = 2;
        while (sq.back() < 1e4)
        {
            sq.push_back(curr * curr);
            curr++;
        }
        long long rv = -1;
        for (long long i = 0; i < n; i++)
        {
            long long r = 0;
            for (long long j = 0; j < sq.size(); j++)
            {
                if ((i + 1) * sq[j] - 1 >= n)
                    break;
                r += nums[(i + 1) * sq[j] - 1];
            }
            rv = max(rv, r);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}