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
    int maxFrequencyScore(vector<int> &nums, long long k)
    {
        int n = nums.size();
        sort(begin(nums), end(nums));

        vector<long long> prefix = {0};
        for (auto i = 0; i < n; ++i)
            prefix.push_back(nums[i] + prefix.back());

        int l = 1, r = n;
        while (l < r)
        {
            int m = (l + r + 1) / 2;

            int f = -1;
            long long sum = 0;
            for (auto i = 0, j = 0; j < nums.size(); ++j)
            {
                sum += nums[j];

                if (j - i + 1 >= m)
                {
                    int l = j - i + 1; 
                    long long median;
                    if (l % 2)
                        median = nums[i + l/2];
                    else
                        median = (nums[i + l / 2 - 1] + nums[i + l / 2]) / 2;

                    auto kk = prev(upper_bound(begin(nums), end(nums), median)) - begin(nums);
                    long long left = median * (kk - i + 1) - (prefix[kk + 1] - prefix[i]);
                    long long right = prefix[j + 1] - prefix[kk + 1] - median * (j - kk);
                    if (left >= 0 && right >= 0 && left + right <= k)
                    {
                        f = m;
                        break;
                    }
                    sum -= nums[i++];
                }
            }

            if (f != -1)
                l = m;
            else
                r = m - 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxFrequencyScore(vector<int>() = {10, 11, 3}, 1);
    cout << r << endl;

    r = sol.maxFrequencyScore(vector<int>() = {10, 19, 26, 18, 27, 18}, 9);
    cout << r << endl;

    r = sol.maxFrequencyScore(vector<int>() = {1, 4, 4, 2, 4}, 0);
    cout << r << endl;

    r = sol.maxFrequencyScore(vector<int>() = {1, 2, 6, 4}, 3);
    cout << r << endl;
}