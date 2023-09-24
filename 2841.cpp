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
    long long maxSum(vector<int> &nums, int m, int k)
    {
        long long sum = 0, rv = 0;
        map<int, int> map;
        for (auto i = 0, j = 0; j < nums.size(); ++j)
        {
            sum += nums[j];
            ++map[nums[j]];
            if (j - i >= k - 1)
            {
                if (map.size() >= m)
                    rv = max(rv, sum);

                sum -= nums[i];
                if (--map[nums[i]] == 0)
                    map.erase(nums[i]);
                ++i;
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxSum(vector<int>() = {2, 6, 7, 3, 1, 7}, 3, 4);
    cout << r << endl;
}