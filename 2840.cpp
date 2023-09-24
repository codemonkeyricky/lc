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
    bool checkStrings(string s1, string s2)
    {
        string even[2], odd[2];
        for (auto i = 0; i < s1.size(); ++i)
            if (i % 2 == 0)
                even[0] += s1[i];
            else
                odd[0] += s1[i];

        for (auto i = 0; i < s2.size(); ++i)
            if (i % 2 == 0)
                even[1] += s2[i];
            else
                odd[1] += s2[i];

        for (auto i = 0; i < 2; ++i)
            sort(begin(even[i]), end(even[i])),
                sort(begin(odd[i]), end(odd[i]));

        return (even[0] == even[1]) && (odd[0] == odd[1]);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}