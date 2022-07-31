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
    bool canChoose(vector<vector<int>> &groups, vector<int> &nums)
    {
        vector<vector<int>> kmps(groups.size());
        for (auto k = 0; k < groups.size(); ++k)
        {
            kmps[k] = vector<int>(groups[k].size());
            int j = 0;
            for (auto i = 1; i < groups[k].size(); ++i)
            {
                while (j > 0 && groups[k][i] != groups[k][j])
                    j = kmps[k][j - 1];
                if (groups[k][i] == groups[k][j])
                    ++j;
                kmps[k][i] = j;
            }
        }

        // kmp

        int j = 0, k = 0;
        for (auto i = 0; i < nums.size();)
            if (k < groups.size())
            {
                if (nums[i] == groups[k][j])
                {
                    ++i, ++j;
                    if (j >= groups[k].size())
                        ++k, j = 0;
                }
                else
                {
                    if (j)
                        j = kmps[k][j - 1];
                    else
                        ++i;
                }
            }
            else
                break;

        return k >= groups.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.canChoose(vector<vector<int>>() = {{9099312, -7882487, -1441304, 6624042, -6043305}}, vector<int>() = {-1441304, 9099312, -7882487, -1441304, 6624042, -6043305, -1441304});
    cout << r << endl;

    r = sol.canChoose(vector<vector<int>>() = {{1, -1, -1}, {3, -2, 0}}, vector<int>() = {1, -1, 0, 1, -1, -1, 3, -2, 0});
    cout << r << endl;

    r = sol.canChoose(vector<vector<int>>() = {{21, 22, 21, 22, 21, 30}}, vector<int>() = {21, 22, 21, 22, 21, 22, 21, 30});
    cout << r << endl;
}