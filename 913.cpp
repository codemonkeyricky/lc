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
    int dfs(vector<vector<int>> &al, int mouse = 1, int cat = 2, int steps = 0)
    {
        if (steps >= al.size() * 2)
            return 0;

        if (mouse == cat)
            return 2;

        if (mouse == 0)
            return 1;

        /*
         *  2 - cat wins
         *  1 - mouse wins
         *  0 = draw
         */

        if (!dp[steps][mouse][cat])
        {
            auto isMouse = steps % 2 == 0;
            if (isMouse)
            {
                int won = false, draw = false;
                for (auto k = 0; k < al[mouse].size() && !won; ++k)
                {
                    int r = dfs(al, al[mouse][k], cat, steps + 1);
                    if (r == 1)
                    {
                        won = true;
                        break;
                    }
                    else if (r == 0)
                        draw = true;
                }

                if (won)
                    dp[steps][mouse][cat] = 1 + 1;
                else if (draw)
                    dp[steps][mouse][cat] = 0 + 1;
                else 
                    dp[steps][mouse][cat] = 2 + 1;
            }
            else 
            {
                int won = false, draw = false;
                for(auto k = 0; k < al[cat].size() && !won; ++k)
                {
                    if (al[cat][k])
                    {
                        int r = dfs(al, mouse, al[cat][k], steps + 1);
                        if (r == 2)
                        {
                            won = true; 
                            break;
                        }
                        else if (r == 0)
                            draw = true;
                    }
                }
                if (won)
                    dp[steps][mouse][cat] = 2 + 1;
                else if (draw)
                    dp[steps][mouse][cat] = 0 + 1;
                else 
                    dp[steps][mouse][cat] = 1 + 1;
            }
        }
        return dp[steps][mouse][cat] - 1;
    }

    vector<vector<vector<int>>> dp;

public:
    int catMouseGame(vector<vector<int>> &graph)
    {
        int n = graph.size();
        dp = vector<vector<vector<int>>>(n * 2, vector<vector<int>>(n, vector<int>(n)));
        return dfs(graph);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.catMouseGame(vector<vector<int>>() = {{5, 7, 9}, {3, 4, 5, 6}, {3, 4, 5, 8}, {1, 2, 6, 7}, {1, 2, 5, 7, 9}, {0, 1, 2, 4, 8}, {1, 3, 7, 8}, {0, 3, 4, 6, 8}, {2, 5, 6, 7, 9}, {0, 4, 8}});
    cout << r << endl;

    r = sol.catMouseGame(vector<vector<int>>() = {{2, 3}, {3, 4}, {0, 4}, {0, 1}, {1, 2}});
    cout << r << endl;

    r = sol.catMouseGame(vector<vector<int>>() = {{1, 3}, {0}, {3}, {0, 2}});
    cout << r << endl;

    r = sol.catMouseGame(vector<vector<int>>() = {{2, 5}, {3}, {0, 4, 5}, {1, 4, 5}, {2, 3}, {0, 2, 3}});
    cout << r << endl;
}