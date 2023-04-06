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
    bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2)
    {
        int i = 0, l = 0, j = 0, k = 0;
        while (i < word1.size() && j < word2.size())
        {
            if (word1[i][l++] != word2[j][k++])
                return false;
            if (l >= word1[i].size())
                l = 0, ++i;
            if (k >= word2[j].size())
                k = 0, ++j;
        }

        if (i < word1.size() || j < word2.size())
            return false;

        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.arrayStringsAreEqual(vector<string>() = {"ab", "c"}, vector<string>() = {"a", "bc"});
    cout << r << endl;
}