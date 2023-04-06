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
    vector<int> answerQueries(vector<int> &nums, vector<int> &queries)
    {
        sort(begin(nums), end(nums));
        vector<int> sum(nums.size() + 1);
        for (auto i = 0; i < nums.size(); ++i)
            sum[i + 1] += sum[i] + nums[i];

        vector<int> rv; 
        for (auto &q : queries)
            rv.push_back(upper_bound(begin(sum), end(sum), q) - begin(sum) - 1);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.answerQueries(vector<int>() = {736411, 184882, 914641, 37925, 214915}, vector<int>() = {718089, 665450});
    cout << r << endl;

    sol.answerQueries(vector<int>() = {4, 5, 2, 1}, vector<int>() = {3, 10, 21});
    cout << r << endl;
}