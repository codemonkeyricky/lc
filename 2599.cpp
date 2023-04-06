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
    int makePrefSumNonNegative(vector<int> &nums)
    {
        priority_queue<long> q;
        long sum = 0, rv = 0;
        for (auto &n : nums)
        {
            if (n < 0)
                q.push(-n);
            sum += n;
            if (sum < 0)
            {
                sum += q.top();
                q.pop();
                ++rv;
            }
        }

        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.makePrefSumNonNegative(vector<int>() = {-3, -1, 1, 0, 3, 0, 5, 5, -1, 1, -4, 4, 4, -2});
    cout << r << endl;

    r = sol.makePrefSumNonNegative(vector<int>() = {6, -6, -3, 3, 1, 5, -4, -3, -2, -3, 4, -1, 4, 4, -2, 6, 0});
    cout << r << endl;

    r = sol.makePrefSumNonNegative(vector<int>() = {3, -5, -2, 6});
    cout << r << endl;

    r = sol.makePrefSumNonNegative(vector<int>() = {2, 3, -5, 4});
    cout << r << endl;
}