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
    int flipLights(int n, int presses)
    {
        bitset<1002> flips[4] = {}, zero = {};
        for (auto i = 1; i <= n; ++i)
            flips[0][i] = 1;
        for (auto i = 2; i <= n; i += 2)
            flips[1][i] = 1;
        for (auto i = 1; i <= n; i += 2)
            flips[2][i] = 1;
        for (auto i = 0; 3 * i + 1 <= n; ++i)
            flips[3][i * 3 + 1] = 1;

        vector<unordered_set<bitset<1002>>> dp(presses + 1);
        queue<pair<bitset<1002>, int>> q;
        dp[presses].insert(flips[0]);
        q.push({flips[0], presses});
        int rv = 0;
        while (q.size())
        {
            auto n = q.front();
            q.pop();

            if (n.second)
            {
                for (auto i = 0; i < 4; ++i)
                {
                    auto mask = (n.first ^ flips[i]) & flips[0];
                    if (!dp[n.second - 1].count(mask))
                        dp[n.second - 1].insert(mask), q.push({mask, n.second - 1});
                }
            }
        }
        return dp[0].size(); 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.flipLights(1, 2);
    cout << r << endl;

    r = sol.flipLights(2, 1);
    cout << r << endl;
}