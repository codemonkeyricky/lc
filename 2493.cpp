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
    bool dfs(int p, int k, vector<vector<int>> &al, vector<int> &group, int id, vector<int> &seen)
    {
        if (seen[k] == 1)
            return group[k] == id;

        if (seen[k] == 2)
            return true;

        if (p && abs(group[p] - id) != 1)
            return false;

        seen[k] = 1;
        group[k] = id;

        int success = true;
        for (auto &n : al[k])
            if (n != p)
            {
                if (dfs(k, n, al, group, id + 1, seen))
                    ;
                else if (dfs(k, n, al, group, id - 1, seen))
                    ;
                else
                {
                    success = false;
                    break;
                }
            }

        if (success)
        {
            seen[k] = 2;
            return true;
        }

        group[k] = seen[k] = 0;
        return false;
    }

    bool bipartite(int k, vector<vector<int>> &al, int b, vector<int> &color, vector<int> &seen)
    {
        if (seen[k] == 2)
            return true;

        if (seen[k] == 1)
            return color[k] == b;

        seen[k] = 1;
        color[k] = b;
        for (auto &n : al[k])
            if (!bipartite(n, al, !b, color, seen))
                return false;
        seen[k] = 1; 
        return true;
    }

    int find(vector<int> &parent, int k)
    {
        if (parent[k] < 0)
            return k; 
        return find(parent, parent[k]);
    }

public:
    int magnificentSets(int n, vector<vector<int>> &edges)
    {
        unordered_set<int> pool;
        vector<vector<int>> al(n + 1);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]), pool.insert(e[0]), pool.insert(e[1]);

        vector<int> seen(n + 1), color(n + 1);
        if (!bipartite(1, al, 0, color, seen))
            return -1;

        vector<int> parent(n + 1, -1);
        for (auto &e : edges)
        {
            auto p1 = find(parent, e[0]);
            auto p2 = find(parent, e[1]);
            if (p1 != p2)
            {
                if (parent[p1] > parent[p2])
                    swap(p1, p2);
                parent[p1] += parent[p2];
                parent[p2] = p1;
            }
        }

        unordered_map<int, int> groups;
        for (auto i = 1; i <= n; ++i)
        {
            int d = 0;
            vector<int> seen(n + 1);
            queue<int> q;
            q.push(i);
            seen[i] = 1;
            while (q.size())
            {
                auto s = q.size();
                while (s)
                {
                    auto n = q.front();
                    q.pop();
                    for (auto &nn : al[n])
                        if (!seen[nn])
                            seen[nn] = 1, q.push(nn);
                    --s;
                }
                ++d;
            }
            groups[find(parent, i)] = max(groups[find(parent, i)], d);
        }

        int rv = 0;
        for (auto &g : groups)
            rv += g.second;

        return rv;//  + n - pool.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.magnificentSets(30, vector<vector<int>>() = {{16, 8}, {6, 5}});
    cout << r << endl;

    r = sol.magnificentSets(3, vector<vector<int>>() = {{1, 2}, {2, 3}, {3, 1}});
    cout << r << endl;

    r = sol.magnificentSets(30, vector<vector<int>>() = {{1, 9}, {30, 27}, {21, 9}, {2, 10}, {16, 28}, {1, 27}, {20, 24}, {22, 24}, {30, 6}, {30, 19}, {1, 19}, {30, 11}, {16, 6}, {16, 29}, {2, 29}, {2, 23}, {16, 24}, {1, 25}, {1, 17}, {16, 23}, {30, 26}, {16, 12}, {1, 14}, {13, 23}, {13, 14}, {2, 19}, {22, 6}, {30, 3}, {30, 18}, {20, 8}, {13, 24}, {20, 9}, {20, 14}, {13, 28}, {13, 10}, {2, 8}, {16, 7}, {16, 10}, {21, 5}, {20, 15}, {20, 11}, {2, 26}, {21, 3}, {22, 10}, {16, 8}, {2, 17}});
    cout << r << endl;

    r = sol.magnificentSets(92, vector<vector<int>>() = {{67, 29}, {13, 29}, {77, 29}, {36, 29}, {82, 29}, {54, 29}, {57, 29}, {53, 29}, {68, 29}, {26, 29}, {21, 29}, {46, 29}, {41, 29}, {45, 29}, {56, 29}, {88, 29}, {2, 29}, {7, 29}, {5, 29}, {16, 29}, {37, 29}, {50, 29}, {79, 29}, {91, 29}, {48, 29}, {87, 29}, {25, 29}, {80, 29}, {71, 29}, {9, 29}, {78, 29}, {33, 29}, {4, 29}, {44, 29}, {72, 29}, {65, 29}, {61, 29}});
    cout << r << endl;

    r = sol.magnificentSets(6, vector<vector<int>>() = {{1, 2}, {1, 4}, {1, 5}, {2, 6}, {2, 3}, {4, 6}});
    cout << r << endl;
}