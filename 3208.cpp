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
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        auto copy = colors;
        for (auto i = 0; i < k - 1; ++i) {
            copy.push_back(colors[i]);
        }
        swap(copy, colors);

        int rv = 0;
        for (int i = 0, j = 0; j < colors.size(); ++j) {

            if (j && colors[j] == colors[j - 1])
                i = j;

            if (j - i + 1 >= k) {
                ++rv;
                ++i;
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.numberOfAlternatingGroups(vector<int>() = {0, 1, 0, 0, 1, 0, 1}, 6);
    cout << r << endl;

    r = sol.numberOfAlternatingGroups(vector<int>() = {0, 1, 0, 1, 0}, 3);
    cout << r << endl;
}