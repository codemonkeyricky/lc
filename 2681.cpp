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
    int sumOfPower(vector<int> &nums)
    {
        int n = nums.size();
        sort(begin(nums), end(nums));

        long long rv = 0, sum = 0, mod = 0;
        for (auto i = 0; i < n; ++i)
        {
            long long add = (long long)nums[i] * nums[i] % 1000000007;
            add = (add * (nums[i] + sum)) % 1000000007;
            rv = (rv + (add)) % 1000000007;
            sum = (sum * 2 + nums[i]) % 1000000007;
        }

        // return !mod ? rv / 2 : rv;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sumOfPower(vector<int>() = {658, 489, 777, 2418, 1893, 130, 2448, 178, 1128, 2149, 1059, 1495, 1166, 608, 2006, 713, 1906, 2108, 680, 1348, 860, 1620, 146, 2447, 1895, 1083, 1465, 2351, 1359, 1187, 906, 533, 1943, 1814, 1808, 2065, 1744, 254, 1988, 1889, 1206});
    cout << r << endl;

    r = sol.sumOfPower(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;

    r = sol.sumOfPower(vector<int>() = {2, 1, 4});
    cout << r << endl;
}