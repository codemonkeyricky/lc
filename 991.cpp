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
    int brokenCalc(int startValue, int target)
    {
        int rv = 0;
        while (target > startValue)
        {
            ++rv;
            if (target % 2 == 1)
                target++;
            else
                target /= 2;
        }

        return rv + startValue - target;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.brokenCalc(3, 100000);
    cout << r << endl;

    r = sol.brokenCalc(3, 10);
    cout << r << endl;

    r = sol.brokenCalc(5, 8);
    cout << r << endl;
}