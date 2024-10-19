#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {

    bool dfs(TreeNode* n, TreeNode* t, vector<TreeNode*>& list) {

        if (n) {

            list.push_back(n);

            if (n == t)
                return true;

            if (dfs(n->left, t, list))
                return true;

            if (dfs(n->right, t, list))
                return true;

            list.pop_back();
        }

        return false;
    }

  public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> l1, l2;
        dfs(root, p, l1);
        dfs(root, p, l2);

        auto s = min(l1.size(), l2.size());
        l1.resize(s), l2.resize(s);

        for (int i = s - 1; i >= 0; --i) {
            if (l1[i] == l2[i])
                return l1[i];
        }

        return nullptr;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
