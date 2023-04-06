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
    long long makeSimilar(vector<int> &nums, vector<int> &target)
    {
        sort(begin(nums), end(nums));
        sort(begin(target), end(target));

        vector<int> src_even, src_odd, dst_even, dst_odd;

        int n = nums.size();
        for (auto i = 0; i < n; ++i)
        {
            if (nums[i] % 2)
                src_odd.push_back(nums[i]);
            else
                src_even.push_back(nums[i]);

            if (target[i] % 2)
                dst_odd.push_back(target[i]);
            else
                dst_even.push_back(target[i]);
        }

        long long pos = 0, neg = 0;
        for (auto i = 0; i < src_even.size(); ++i)
            if (src_even[i] > dst_even[i])
                pos += src_even[i] - dst_even[i];
            else 
                neg += dst_even[i] - src_even[i];

        for (auto i = 0; i < src_odd.size(); ++i)
            if (src_odd[i] > dst_odd[i])
                pos += src_odd[i] - dst_odd[i];
            else 
                neg += dst_odd[i] - src_odd[i];

        return pos / 2;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.makeSimilar(vector<int>() = {758, 334, 402, 1792, 1112, 1436, 1534, 1702, 1538, 1427, 720, 1424, 114, 1604, 564, 120, 578}, vector<int>() = {1670, 216, 1392, 1828, 1104, 464, 678, 1134, 644, 1178, 1150, 1608, 1799, 1156, 244, 2, 892});
    cout << r << endl;

    r = sol.makeSimilar(vector<int>() = {1, 2, 5}, vector<int>() = {4, 1, 3});
    cout << r << endl;

    r = sol.makeSimilar(vector<int>() = {8, 12, 6}, vector<int>() = {2, 14, 10});
    cout << r << endl;
}