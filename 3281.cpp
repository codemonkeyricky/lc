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

class Solution {
  public:
    int maxPossibleScore(vector<int>& start, int d) {
        sort(begin(start), end(start));

        long long l = 0, r = start.back() + d;

        while (l < r) {
            long long m = (l + r + 1) / 2;
            int too_big = false, too_small = false;
            long long c = start[0];
            for (auto k = 1; k < start.size(); ++k) {
                if (c + m > start[k] + d) {
                    too_big = true;
                    break;
                }
                c = max(c + m, (long long)start[k]);
            }
            if (too_big)
                r = m - 1;
            else
                l = m;
        }
        return l;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.maxPossibleScore(vector<int>() = {0, 9, 2, 9}, 2);
    cout << r << endl;

    r = sol.maxPossibleScore(vector<int>() = {2, 6, 13, 13}, 5);
    cout << r << endl;

    r = sol.maxPossibleScore(vector<int>() = {6, 0, 3}, 2);
    cout << r << endl;
}
