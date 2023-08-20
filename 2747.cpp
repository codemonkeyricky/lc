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
    vector<int> countServers(int n, vector<vector<int>> &logs, int x, vector<int> &queries)
    {
        vector<array<int, 2>> time_id;
        for (auto &l : logs)
            time_id.push_back({l[1], l[0]});
        sort(begin(time_id), end(time_id));

        vector<array<int, 2>> q;
        for (auto k = 0; k < queries.size(); ++k)
            q.push_back({queries[k], k});
        sort(begin(q),end(q));

        vector<int> rv(q.size());
        map<int, int> map;
        for (auto i = 0, j = 0, k = 0; k < q.size(); ++k)
        {
            while (j < time_id.size() && time_id[j][0] <= q[k][0])
                ++map[time_id[j++][1]];

            while (i < time_id.size() && q[k][0] - x > time_id[i][0])
            {
                if (--map[time_id[i][1]] == 0)
                    map.erase(time_id[i][1]);
                ++i;
            }
            rv[q[k][1]] = n - map.size();
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> rv;

    rv = sol.countServers(6, vector<vector<int>>() = {{1, 21}}, 10, vector<int>() = {24, 35, 28, 26, 20, 25, 16, 31, 12});
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;

    rv = sol.countServers(3, vector<vector<int>>() = {{1, 3}, {2, 6}, {1, 5}}, 5, vector<int>() = {10, 11});
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;
}