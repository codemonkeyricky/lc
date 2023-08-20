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
    long long continuousSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        map<int, int> map;
        long long rv = 0;
        for (auto i = 0ll, j = 0ll; j < n; ++j)
        {
            ++map[nums[j]];
            while (prev(map.end())->first - map.begin()->first > 2)
            {
                --map[nums[i]];
                if (map[nums[i]] == 0)
                    map.erase(nums[i]);
                ++i;
            }
            rv += j - i + 1;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.continuousSubarrays(vector<int>() = {5, 4, 2, 4});
    cout << r << endl;
}