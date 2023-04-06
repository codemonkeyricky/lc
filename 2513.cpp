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
    int minimizeSet(int div1, int div2, int uniqCnt1, int uniqCnt2)
    {
        int l = 1, r = 2e9;
        while (l < r)
        {
            int m = (l + r) / 2;
            long lcm = std::lcm((long)div1, (long)div2);
            int arr1 = m / div2 - m / lcm;
            int arr2 = m / div1 - m / lcm;
            int arr1_arr2 = m - m / div1 - m / div2 + m / lcm;
            int u1 = uniqCnt1, u2 = uniqCnt2;
            u1 = u1 - min(u1, arr1);
            int remove = min(u1, arr1_arr2);
            u1 = u1 - remove, arr1_arr2 -= remove;
            u2 = u2 - min(u2, arr2);
            u2 = u2 - min(u2, arr1_arr2);
            if (!u1 && !u2)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimizeSet(78789, 42659, 58291, 182389);
    cout << r << endl;

    r = sol.minimizeSet(2, 4, 8, 2);
    cout << r << endl;

    r = sol.minimizeSet(2, 7, 1, 3);
    cout << r << endl;
}