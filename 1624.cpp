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

class Solution {
public:
   int maxLengthBetweenEqualCharacters(string s) {
    int idx[26] = {}, res = -1;
    for (auto i = 0; i < s.size(); ++i) {
        if (idx[s[i] - 'a'] == 0)
            idx[s[i] - 'a'] = i + 1;
        res = max(res, i - idx[s[i] - 'a']);
    }
    return res;
} 
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}