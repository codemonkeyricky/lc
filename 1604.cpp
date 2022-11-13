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
    vector<string> alertNames(vector<string> &name, vector<string> &time)
    {
        int n = name.size(); 
        map<string, vector<int>> asset;
        for (auto i = 0; i < n; ++i)
        {
            auto h = time[i][0] * 10 + time[i][1];
            auto m = time[i][3] * 10 + time[i][4];
            asset[name[i]].push_back(h * 60 + m);
        }

        vector<string> rv;
        for (auto &a : asset)
        {
            int found = false;
            sort(begin(a.second), end(a.second));
            for (auto i = 2; i < a.second.size() && !found; ++i)
                if(a.second[i] - a.second[i-2] <= 60)
                    rv.push_back(a.first), found = true;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}
