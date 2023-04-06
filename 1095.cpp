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


// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray {
  public:
    int get(int index);
    int length();
};

class Solution
{
public:
    int findInMountainArray(int target, MountainArray &mountainArr)
    {
        int n = mountainArr.length();
        int l = 1, r = n - 1;
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            if (mountainArr.get(m - 1) < mountainArr.get(m))
                l = m;
            else 
                r = m - 1; 
        }
        auto peak = l;
        l = 0, r = peak;
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            int get = mountainArr.get(m);
            if (get <= target)
                l = m;
            else
                r = m - 1;
        }

        if (mountainArr.get(l) == target)
            return l;

        l = peak + 1, r = n - 1;
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            int get = mountainArr.get(m);
            if (get >= target)
                l = m;
            else
                r = m - 1;
        }
        if (mountainArr.get(l) == target)
            return l;

        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}