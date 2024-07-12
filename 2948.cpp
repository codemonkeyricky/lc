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
    vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit)
    {
        set<int> uniq;
        for (auto &n : nums)
            uniq.insert(n);

        unordered_map<int, int> lookup;
        int k = 0, p = -1;
        for (auto &u : uniq)
        {
            if (u == *uniq.begin())
                lookup[u] = k;
            else 
            {
                if (u - p <= limit)
                    lookup[u] = k;
                else
                    lookup[u] = ++k;
            }
            p = u;
        }

        vector<multiset<int>> groups(k + 1);
        for (auto &n : nums)
            groups[lookup[n]].insert(n);

        vector<int> rv;
        for (auto &n : nums)
            rv.push_back(*groups[lookup[n]].begin()),
                groups[lookup[n]].erase(groups[lookup[n]].begin());

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.lexicographicallySmallestArray(vector<int>() = {1, 5, 3, 9, 8}, 2);
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}