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
    string restoreString(string s, vector<int> &indices)
    {
        for (int i = 0; i < indices.size(); i++)
            while (indices[i] != i)
            {
                swap(s[i], s[indices[i]]);
                swap(indices[i], indices[indices[i]]);
            }

        return s;
    }
};

int main()
{
    Solution sol;
    string s; 

    s = sol.restoreString("codeleet", vector<int>() = {4, 5, 6, 7, 0, 2, 1, 3});
    cout << s << endl;
}