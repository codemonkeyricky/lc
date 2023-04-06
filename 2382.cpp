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
    vector<long long> maximumSegmentSum(vector<int> &nums, vector<int> &removeQueries)
    {
        int n = nums.size();
        vector<long long> sum(n + 1);
        for (auto i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + nums[i - 1];

        multiset<long long> segs = {sum.back()};
        set<int> removed = {0, n + 1};
        vector<long long> rv; 
        for (auto &q : removeQueries)
        {
            auto j = removed.lower_bound(q + 1);
            auto i = prev(j);
            segs.erase(segs.find(sum[*j - 1] - sum[*i]));
            if (q + 1 - *i > 1)
                segs.insert(sum[q] - sum[*i]);
            if (*j - (q + 1) > 1)
                segs.insert(sum[*j - 1] - sum[q + 1]);
            removed.insert(q + 1);
            rv.push_back(segs.size() ? *segs.rbegin() : 0);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    sol.maximumSegmentSum(vector<int>() = {1, 2, 5, 6, 1}, vector<int>() = {0, 3, 2, 4, 1});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}