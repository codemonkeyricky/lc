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
    vector<long long> distance(vector<int> &nums)
    {
        vector<long long> rv;
        map<int, vector<array<long long, 2>>> map;
        for (auto i = 0; i < nums.size(); ++i)
            map[nums[i]].push_back({i, 0});

        for (auto &m : map)
            for (auto i = 0; i < m.second.size(); ++i)
                m.second[i][1] = m.second[i][0] + (i ? m.second[i - 1][1] : 0);

        for (auto i = 0; i < nums.size(); ++i)
        {
            auto &v = map[nums[i]];
            auto sz = v.size();
            array<long long, 2> vv = {i, 0};
            auto k = lower_bound(begin(v), end(v), vv) - begin(v);
            auto l = i * k;
            if (k)
                l -= v[k - 1][1];
            auto r = (v.back()[1] - v[k][1]) - (sz - k - 1) * i;
            rv.push_back(l + r);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.distance(vector<int>() = {1, 3, 1, 1, 2});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl; 
}