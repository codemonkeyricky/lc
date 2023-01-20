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
    bool isSubset(vector<vector<string>> &fav, int i, int j)
    {
        int k, l;
        for (k = 0, l = 0; k < fav[i].size() && l < fav[j].size(); ++k)
        {
            while (l < fav[j].size() && fav[i][k] != fav[j][l])
                ++l;
            if (l >= fav[j].size())
                break;
        }
        return k >= fav[i].size();
    }

public:
    vector<int> peopleIndexes(vector<vector<string>> &fav)
    {
        for (auto &f : fav)
            sort(begin(f), end(f));

        int n = fav.size();
        vector<int> rv; 
        for (auto i = 0; i < n; ++i)
        {
            int j;
            for (j = 0; j < n; ++j)
                if (i != j)
                    if (isSubset(fav, i, j))
                        break;
            if (j >= n)
                rv.push_back(i);
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.peopleIndexes(vector<vector<string>>() = {{"leetcode", "google", "facebook"}, {"google", "microsoft"}, {"google", "facebook"}, {"google"}, {"amazon"}});
}