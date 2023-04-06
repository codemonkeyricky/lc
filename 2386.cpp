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
    using type = array<long long, 2>;
public:
    long long kSum(vector<int> &nums, int k)
    {
        long long sum = 0;
        for (auto &n : nums)
        {
            if (n > 0)
                sum += n;
            n = abs(n);
        }

        sort(begin(nums), end(nums));

        priority_queue<type> q;
        q.push({sum - nums[0], 0});
        vector<long long> rv = {sum};
        while (rv.size() < k)
        {
            auto [sum, i] = q.top();
            q.pop();
            rv.push_back(sum);
            if (i + 1 < nums.size())
            {
                q.push({sum + nums[i] - nums[i + 1], i + 1});
                q.push({sum - nums[i + 1], i + 1});
            }
        }
        return rv[k-1]; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.kSum(vector<int>() = {-1, 1}, 1);
    cout << r << endl;

    r = sol.kSum(vector<int>() = {2, 4, -2}, 5);
    cout << r << endl;
}