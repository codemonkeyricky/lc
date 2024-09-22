#include <algorithm>
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

class Solution {
  public:
    bool doesAliceWin(string s) {

        int v = 0;
        for (auto& c : s) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                ++v;
        }

        return v % 2;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.doesAliceWin("bbcd");
    cout << r << endl;

    r = sol.doesAliceWin("leetcoder");
    cout << r << endl;
}