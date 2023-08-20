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

// class Solution
// {
//     void dfs(vector<int> &order, int index, int assign, vector<vector<int>> &rv, int target, int real)
//     {
//         if (assign == 0)
//             return;

//         if (index + 1 >= order.size())
//             return;

//         for (auto &next : al[order[index]])
//         {
//             auto v = next.first;
//             auto w = next.second;
//             if (v == order[index + 1])
//             {
//                 int a = order[index], b = next.first;
//                 if (a > b)
//                     swap(a, b);
//                 auto p = lookup[{a, b}];

//                 auto n = next.first;
//                 auto w = next.second;
//                 auto assigned = 0;
//                 if (w == -1)
//                 {
//                     if (assign-- > 1)
//                         w = rv[p][2] = 1;
//                     else
//                         w = rv[p][2] = target - real;
//                     assigned = true;
//                 }

//                 dfs(order, index + 1, assign, rv, target - w, real - (assigned ? 0 : w));
//                 break;
//             }
//         }
//     }

//     vector<map<int, int>> al;
//     map<array<int, 2>, int> lookup;

//     int dijkstra(int src, int dst)
//     {
//         // total / node / seen
//         priority_queue<tuple<int, int, __int128>> q;
//         q.push({0, src, (__int128)1 << src});
//         while (q.size())
//         {
//             auto [total, k, seen] = q.top();
//             q.pop();
//             if (k == dst)
//                 return -total;

//             for (auto &next : al[k])
//             {
//                 auto v = next.first;
//                 auto w = next.second;
//                 if (w != -1 && !(seen & ((__int128)1 << v)))
//                     q.push({total - w, v, seen | ((__int128)1 << v)});
//             }
//         }
//         return -1;
//     }

// public:
//     vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>> &edges, int src, int dst, int target)
//     {
//         al = vector<map<int, int>>(n);
//         for (auto i = 0; i < edges.size(); ++i)
//         {
//             auto a = edges[i][0];
//             auto b = edges[i][1];
//             auto c = edges[i][2];
//             if (a > b)
//                 swap(a, b);
//             al[a][b] = c; 
//             al[b][a] = c;
//             lookup[{a, b}] = i;
//         }

//         int rv = dijkstra(src, dst);
//         if (rv != -1 && rv < target)
//             return {};

//         // total minimal weight / real weight / node / assign / order / seen
//         priority_queue<tuple<int, int, int, int, vector<int>, set<int>>> q;
//         int assign = 0, real = 0;
//         vector<int> vec = {src}, order;
//         set<int> set = {src}, seen;
//         q.push({0, 0, src, 0, vec, set});
//         while (q.size())
//         {
//             auto p = q.top();
//             auto [total, r, k, a, o, s] = q.top();
//             q.pop();
//             if (dst == k) 
//             {
//                 if (-total == target || (-total < target && a))
//                 {
//                     order = o;
//                     seen = s;
//                     assign = a;
//                     real = r;
//                     break;
//                 }
//                 else
//                     continue;
//             }

//             for (auto &next : al[k])
//             {
//                 auto node = next.first;
//                 auto cost = next.second;
//                 if (!s.count(node))
//                 {
//                     s.insert(node); 
//                     o.push_back(node);
//                     q.push({total - ((next.second == -1) ? 1 : next.second),
//                             r + ((next.second == -1) ? 0 : next.second),
//                             node,
//                             a + ((next.second == -1) ? 1 : 0),
//                             o,
//                             s});
//                     o.pop_back();
//                     s.erase(node);
//                 }
//             }
//         }

//         if (seen.size()) 
//         {
//             auto rv = edges;
//             if (assign)
//             {
//                 dfs(order, 0, assign, rv, target, real);
//                 for (auto &e : rv)
//                     if (e[2] == -1)
//                         e[2] = 1;
//             }
//             return rv;
//         }

//         return {};
//     }
// };

class Solution
{
    int dfs(int target, int so_far, int dst, int p, int k, vector<int> &seen, int assign, vector<vector<int>> &edges)
    {
        if (k == dst)
        {
            int rv = 0;
            auto a = p, b = k;
            if (a > b)
                swap(a, b);
            auto pp = lookup[{a, b}];

            if (edges[pp][2] == -1)
            {
                if (assign > 1)
                    edges[pp][2] = 1;
                else if (assign == 1)
                {
                    auto add = target - so_far - rv;
                    if (add < 1)
                        edges[pp][2] = 1e9;
                    else
                        edges[pp][2] = add;
                }
                rv = min(rv + edges[pp][2], (int)1e9);
            }
            else if (assign == 0 && so_far < target)
                rv = 1e9;

            return rv;
        }

        int rv = 1e9;
        if (!seen[k])
        {
            seen[k] = 1;
            for (auto &next : al[k])
            {
                auto v = next.first;
                auto w = next.second;
                if (v != p)
                    rv = min(rv, dfs(target, so_far + (w == -1 ? 0 : w), dst, k, v, seen, assign + (w == -1), edges));
            }

            if (p != -1)
            {
                auto a = p, b = k;
                if (a > b)
                    swap(a, b);
                auto pp = lookup[{a, b}];
                if (edges[pp][2] == -1)
                    if (assign > 1)
                        edges[pp][2] = 1;
                    else if (assign == 1)
                    {
                        auto add = target - so_far - rv;
                        if (add < 1)
                            edges[pp][2] = 1e9;
                        else
                            edges[pp][2] = add;
                    }
                rv = min(rv + edges[pp][2], (int)1e9);
            }
            seen[k] = 2;
        }
        return rv;
    }

    vector<map<int, int>> al;
    map<array<int, 2>, int> lookup;

public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>> &edges, int source, int destination, int target)
    {
        al = vector<map<int, int>>(n);
        for (auto i = 0; i < edges.size(); ++i)
        {
            auto a = edges[i][0];
            auto b = edges[i][1];
            auto c = edges[i][2];
            if (a > b)
                swap(a, b);
            al[a][b] = c;
            al[b][a] = c;
            lookup[{a, b}] = i;
        }

        vector<int> seen(101);
        auto rv = dfs(target, 0, destination, -1, source, seen, 0, edges);
        vector<vector<int>> empty;
        return rv < 1e9 ? edges : empty;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> rv;

    // rv = sol.modifiedGraphEdges(4,
    //                             vector<vector<int>>() = {{0, 1, -1}, {2, 0, 2}, {3, 2, 6}, {2, 1, 10}, {3, 0, -1}},
    //                             1, 3, 12);
    // for (auto &r : rv)
    //     cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    // cout << endl;

    // rv = sol.modifiedGraphEdges(5,
    //                             vector<vector<int>>() = {{1, 4, -1}, {0, 2, -1}, {0, 3, 9}, {4, 0, -1}, {1, 0, 10}, {4, 2, 10}},
    //                             1, 2, 9);
    // for (auto &r : rv)
    //     cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    // cout << endl;


    // rv = sol.modifiedGraphEdges(5,
    //                             vector<vector<int>>() = {{3, 0, 1}, {2, 1, -1}, {2, 3, 6}, {4, 2, 6}, {1, 3, 2}, {2, 0, 7}, {0, 4, 10}, {0, 1, 6}},
    //                             1, 4, 14);
    // for (auto &r : rv)
    //     cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    // cout << endl;

    rv = sol.modifiedGraphEdges(5,
                                vector<vector<int>>() = {{1, 3, 10}, {4, 2, -1}, {0, 3, 7}, {4, 0, 7}, {3, 2, -1}, {1, 4, 5}, {2, 0, 8}, {1, 0, 3}, {1, 2, 5}},
                                3, 4, 11);
    for (auto &r : rv)
        cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    cout << endl;

    // rv = sol.modifiedGraphEdges(4, vector<vector<int>>() = {{1, 0, 4}, {1, 2, 3}, {2, 3, 5}, {0, 3, -1}}, 0, 2, 6);
    // for (auto &r : rv)
    //     cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    // cout << endl;

    rv = sol.modifiedGraphEdges(3, vector<vector<int>>() = {{0, 1, -1}, {0, 2, 5}}, 0, 2, 6);
    for (auto &r : rv)
        cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    cout << endl;

    rv = sol.modifiedGraphEdges(5, vector<vector<int>>() = {{4, 1, -1}, {2, 0, -1}, {0, 3, -1}, {4, 3, -1}}, 0, 1, 5);
    for (auto &r : rv)
        cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    cout << endl;
}