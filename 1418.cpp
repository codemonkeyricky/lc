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
    vector<vector<string>> displayTable(vector<vector<string>> &orders)
    {
        map<int, map<string, int>> dp;
        set<string> types;
        for (auto &order : orders)
            ++dp[stoi(order[1])][order[2]], types.insert(order[2]);

        vector<vector<string>> rv;
        vector<string> hdr = {"Table"};
        hdr.insert(hdr.end(), begin(types), end(types));
        rv.push_back(hdr);
        for (auto &d : dp)
        {
            vector<string> row;
            row.push_back(to_string(d.first));
            for (auto &type : types)
                row.push_back(to_string(d.second[type]));
            rv.push_back(row);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.displayTable(vector<vector<string>>() = {{"David", "3", "Ceviche"}, {"Corina", "10", "Beef Burrito"}, {"David", "3", "Fried Chicken"}, {"Carla", "5", "Water"}, {"Carla", "5", "Ceviche"}, {"Rous", "3", "Ceviche"}});
}