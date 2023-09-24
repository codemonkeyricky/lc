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
    int minimumSeconds(vector<vector<string>> &land)
    {
        int m = land.size();
        int n = land[0].size();

        queue<array<int, 3>> q;
        array<int, 2> d, s;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                if (land[i][j] == "*")
                    q.push({i, j, 0});
                else if (land[i][j] == "S")
                    s = {i, j};
                else if (land[i][j] == "D")
                    d = {i, j};

        vector<int> dir = {0, 1, 0, -1, 0};
        vector<vector<int>> visited(m, vector<int>(n));
        int rv = 0;
        q.push({s[0], s[1], 1});
        while (q.size())
        {
            auto s = q.size();
            while (s)
            {
                auto [i, j, p] = q.front();
                if (i == d[0] && j == d[1] && p)
                    return rv;
                q.pop();

                for (auto k = 0; k < 4; ++k)
                {
                    auto x = i + dir[k + 0];
                    auto y = j + dir[k + 1];
                    if (x >= 0 && x < m && y >= 0 && y < n)
                        if (p == 0)
                        {
                            if (land[x][y] != "X" && land[x][y] != "D" && land[x][y] != "*")
                            {
                                land[x][y] = "*";
                                q.push({x, y, 0});
                            }
                        }
                        else if (p == 1)
                        {
                            if (land[x][y] == "." || land[x][y] == "D")
                            {
                                land[x][y] = "S";
                                q.push({x, y, 1});
                            }
                        }
                }
                --s;
            }
            ++rv; 
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumSeconds(vector<vector<string>>() = {{"D", "X", "*"}, {".", ".", "."}, {".", ".", "S"}});
    cout << r << endl;

    r = sol.minimumSeconds(vector<vector<string>>() = {{"D", ".", "*"}, {".", ".", "."}, {".", "S", "."}});
    cout << r << endl;
}