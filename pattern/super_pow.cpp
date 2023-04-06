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
    int MOD = 1000000007;
    long superPow(int n, int p)
    {
        if (p == 0)
            return 0;

        if (p == 1)
            return n;

        long rr = superPow(n, p / 2);
        long rv = rr * rr % MOD;
        if (p % 2)
            rv = rv * n % MOD;
        return rv;
    }

public:
    int maxFrequencyScore(vector<int> &nums, int k)
    {
        int score = 0, MOD = 1000000007;
        vector<int> count(1000001);
        long sum = 0, rv = 0;
        for (auto i = 0; i <= nums.size(); ++i)
        {
            if (i >= k)
                rv = max(rv, sum);

            if (i < nums.size())
            {
                if (count[nums[i]] != 0)
                    sum -= superPow(nums[i], count[nums[i]]);
                sum = (sum + superPow(nums[i], ++count[nums[i]])) % MOD;
                while (sum < 0)
                    sum += MOD;
            }

            if (i >= k)
            {
                sum -= superPow(nums[i - k], count[nums[i - k]]);
                sum = (sum + superPow(nums[i - k], --count[nums[i - k]])) % MOD;
                while (sum < 0)
                    sum += MOD;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxFrequencyScore(vector<int>() = {1,3,2,3,3,3,1,3,3,1,1,1,1,3,2,2,3,3,2,2,2,3,2,2,2,1,1,3,1,2,2,1,1,1,1,1,2,3,1,1,2,2,1,1,2,3,3,2,2,2,2,1,1,1,3,1,3,3,3,3,1,2,1,2,2,2,2,2,1,1,2,3,3,3,1,1,1,2,1,3,2,2,2,1,1,1,1,2,1,2,}, 100);
    cout << r << endl;

    r = sol.maxFrequencyScore(vector<int>() = {1, 1, 1, 2, 1, 2}, 3);
    cout << r << endl;
}
