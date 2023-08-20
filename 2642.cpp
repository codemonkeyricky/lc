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

class Graph
{
    int djk(int i, int j)
    {
        int n = al.size();
        priority_queue<array<int, 2>> q;
        vector<int> seen(n);
        seen[i] = 1;
        q.push({0, i});
        int rv = 1e9;
        while (q.size())
        {
            auto [c, k] = q.top();
            q.pop();

            seen[k] = 1;

            if (k == j)
                return -c;

            for (auto &[n, w] : al[k])
                if (!seen[n])
                     q.push({c - w, n});
        }

        return -1;
    }

    vector<map<int, int>> al;

public:
    Graph(int n, vector<vector<int>> &edges)
    {
        al = vector<map<int, int>>(n);
        for (auto &e : edges)
            addEdge(e);
    }

    void addEdge(vector<int> edge)
    {
        al[edge[0]][edge[1]] = edge[2];
    }

    int shortestPath(int node1, int node2)
    {
        return djk(node1, node2);
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */

int main()
{
    Graph g(4, vector<vector<int>>() = {{0, 2, 5}, {0, 1, 2}, {1, 2, 1}, {3, 0, 3}});
    cout << g.shortestPath(3, 2) << endl;
}