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
    vector<int> maxScoreIndices(vector<int> &nums)
    {
        auto ones = accumulate(begin(nums), end(nums), 0, [](const int mask, const int v)
                               { return mask + v; });

        vector<int> rv;
        int zeros = 0, score = -1; 
        for (auto i = 0; i <= nums.size(); ++i)
        {
            if (zeros + ones > score)
                score = zeros + ones, rv.clear();

            if (score == zeros + ones)
                rv.push_back(i);

            if (i < nums.size())
                zeros += !nums[i], ones -= nums[i];
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.maxScoreIndices(vector<int>() = {0, 0, 1, 0});
    cout << r << endl;
}