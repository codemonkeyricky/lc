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
    bool sequenceReconstruction(vector<int> &nums, vector<vector<int>> &sequences)
    {
        auto mm = *max_element(begin(nums), end(nums));

        vector<unordered_set<int>> al(mm + 1);
        for (auto &seq : sequences)
            for (auto i = 1; i < seq.size(); ++i)
                al[seq[i - 1]].insert(seq[i]);

        for (auto i = 1; i < nums.size(); ++i)
            if (!al[nums[i - 1]].count(nums[i]))
                return false;

        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}