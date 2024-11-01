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

class Solution {
    TreeNode* dfs(TreeNode* node) {

        if (node) {

            /* flatten the left subtree */

            auto l = dfs(node->left);
            auto r = dfs(node->right);

            /* nullptr left */
            node->left = nullptr;

            auto tmp = l;
            while (tmp && tmp->right)
                tmp = tmp->right;

            if (tmp)
                tmp->right = r;
            else
                l = r;

            node->left = l;
            node->right = r; 

            return node;
        }

        return nullptr;
    }

  public:
    void flatten(TreeNode* root) { dfs(root); }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}