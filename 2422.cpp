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
    int minimumOperations(vector<int> &nums)
    {
        int i = 0, j = nums.size() - 1;
        long lsum = 0, rsum = 0;
        int rv = 0;
        while (i <= j)
        {
            if (lsum == rsum)
                lsum = nums[i++], rsum = nums[j--];
            else if (lsum < rsum)
                lsum += nums[i++], ++rv; 
            else 
                rsum += nums[j--], ++rv;
        }
        return rv + (lsum != rsum);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumOperations(vector<int>() = {1, 2, 3, 4});
    cout << r << endl;

    r = sol.minimumOperations(vector<int>() = {4, 3, 2, 1, 2, 3, 1});
    cout << r << endl;
}