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
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int l = 0, r = arr.size();
        while (l < r)
        {
            auto m = (l + r + 1) / 2;
            if (m && arr[m - 1] < arr[m])
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

    r = sol.peakIndexInMountainArray(vector<int>() = {0, 10, 5, 2});
    cout << r << endl;

    r = sol.peakIndexInMountainArray(vector<int>() = {0, 2, 1, 0});
    cout << r << endl;

    r = sol.peakIndexInMountainArray(vector<int>() = {0, 1, 0});
    cout << r << endl;
}