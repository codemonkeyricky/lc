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
    int miceAndCheese(vector<int> &reward1, vector<int> &reward2, int k)
    {
        vector<array<int,2>> diff; 
        int n = reward1.size();
        for (auto i = 0; i < n; ++i)
            diff.push_back({reward1[i] - reward2[i], i});

        sort(begin(diff), end(diff));
        int kk = 0;
        int rv = 0;
        for (auto it = rbegin(diff); it != rend(diff); ++kk, ++it)
            if (kk < k)
                rv += reward1[(*it)[1]];
            else 
                rv += reward2[(*it)[1]];
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}