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
    int minOperations(vector<int> &nums)
    {
        vector<int> cnt(1e6 + 1);
        for (auto &n : nums)
            ++cnt[n];
        
        int rv = 0;
        for (auto &c : cnt)
            if (c)
                if (c == 1)
                    return -1;
                else
                {
                    while (c && c != 4 && c != 2)
                        ++rv, c -= 3;
                    rv += c / 2;
                }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {2, 3, 3, 2, 2, 4, 2, 3, 4});
    cout << r << endl;
}