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
    class Compare
    {
    public:
        bool operator()(string &l, string &r)
        {
            if(l.size() != r.size())
                return l.size() > r.size();
            return l > r;
        }
    };

    array<int, 2> getPos(string &p, array<int, 2> ball)
    {
        array<int, 2> b = ball;
        for (auto &pp : p)
            if (pp == 'u')
                --b[0];
            else if (pp == 'd')
                ++b[0];
            else if (pp == 'l')
                --b[1];
            else if (pp == 'r')
                ++b[1];
        return b;
    }

public:
    string findShortestWay(vector<vector<int>> &maze, vector<int> &ball, vector<int> &hole)
    {
        int m = maze.size();
        int n = maze[0].size();
        vector<vector<string>> seen(m, vector<string>(n));
        priority_queue<string, vector<string>, Compare> q;
        vector<int> offset = {0, -1, 0, 1, 0};
        vector<string> dir_str = {"l", "u", "r", "d"};
        q.push("");
        while (q.size())
        {
            auto dir = q.top();
            q.pop();
            auto [i, j] = getPos(dir, {ball[0], ball[1]});

            for (auto k = 0; k < 4; ++k)
            {
                int ii = i, jj = j;
                string dd; 
                while (true)
                {
                    auto ni = ii + offset[k + 0];
                    auto nj = jj + offset[k + 1];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && !maze[ni][nj])
                        ii = ni, jj = nj;
                    else
                        break;
                    dd += dir_str[k];

                    if (ii == hole[0] && jj == hole[1])
                        break;
                }

                string a = dir + dd;
                string b = seen[ii][jj];
                if (b.empty() || a.size() < b.size() || (a.size() == b.size() && a < b))
                {
                    if (!(ii == ball[0] && jj == ball[1]))
                    {
                        seen[ii][jj] = a;
                        q.push(a);
                    }
                }
            }
        }

        string rv = seen[hole[0]][hole[1]];
        string rrv ;
        for (auto i = 0; i < rv.size(); ++i)
            if (i == 0)
                rrv += rv[i];
            else if (rv[i] != rv[i - 1])
                rrv += rv[i];
        swap(rv, rrv);
        return rv.empty() ? "impossible" : rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.findShortestWay(vector<vector<int>>() = {{0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
                                                     {0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
                                                     {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                                                     {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                                                     {0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
                                                     {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                                                     {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                                     {0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
                                                     {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}},
                            vector<int>() = {2, 4}, vector<int>() = {7, 6});
    cout << r << endl;

    r = sol.findShortestWay(vector<vector<int>>() = {{0, 0, 1, 0, 0},
                                                     {0, 0, 0, 0, 0},
                                                     {0, 0, 0, 1, 0},
                                                     {1, 1, 0, 1, 1},
                                                     {0, 0, 0, 0, 0}},
                            vector<int>() = {1, 1}, vector<int>() = {1, 2});
    cout << r << endl;

    r = sol.findShortestWay(vector<vector<int>>() = {{0, 0, 1, 0, 0},
                                                     {0, 0, 0, 0, 0},
                                                     {0, 0, 0, 1, 0},
                                                     {1, 1, 0, 1, 1},
                                                     {0, 0, 0, 0, 0}},
                            vector<int>() = {0, 4}, vector<int>() = {0, 1});
    cout << r << endl;


    r = sol.findShortestWay(vector<vector<int>>() = {{0, 0, 0, 0, 0},
                                                     {1, 1, 0, 0, 1},
                                                     {0, 0, 0, 0, 0},
                                                     {0, 1, 0, 0, 1},
                                                     {0, 1, 0, 0, 0}},
                            vector<int>() = {4, 3}, vector<int>() = {0, 1});
    cout << r << endl;
}