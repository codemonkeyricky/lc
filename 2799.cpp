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
    int countCompleteSubarrays(vector<int> &nums)
    {
        auto uniq = unordered_set<int>(begin(nums), end(nums)).size();

        int n = nums.size();
        map<int,int> m;
        int rv = 0;
        for (auto i = 0; i < n; ++i, m.clear())
            for (auto j = i; j < n; ++j)
            {
                ++m[nums[j]];
                if(m.size() == uniq)
                    ++rv;
            }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countCompleteSubarrays(vector<int>() = {1898, 370, 822, 1659, 1360, 128, 370, 360, 261, 1898});
    cout << r << endl;

    r = sol.countCompleteSubarrays(vector<int>() = {5, 5, 5, 5});
    cout << r << endl;

    r = sol.countCompleteSubarrays(vector<int>() = {1, 3, 1, 2, 2});
    cout << r << endl;
}