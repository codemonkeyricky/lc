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
    int captureForts(vector<int> &forts)
    {
        int rv = 0;
        for (auto i = 0, j = 0; j < forts.size(); ++j)
            if (forts[j] != 0)
            {
                if ((forts[i] == 1 && forts[j] == -1) || (forts[i] == -1 && forts[j] == 1))
                    rv = max(rv, j - i - 1);
                i = j;
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.captureForts(vector<int>() = {0, 0, 1, -1});
    cout << r << endl;

    r = sol.captureForts(vector<int>() = {1, 0, 0, -1, 0, 0, 0, 0, 1});
    cout << r << endl;
}