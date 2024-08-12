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

  return new TreeNode(
      tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

class Solution {
 public:
  bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    if (sx == fx && sy == fy)
      return t != 1;

    int x = abs(sx - fx);
    int y = abs(sy - fy);

    int min_t = abs(x - y) + min(x, y);
    return t >= min_t;
  }
};

int main() {
  Solution sol;
  int r;

  r = sol.isReachableAtTime(1, 1, 1, 1, 3);
  cout << r << endl;

  r = sol.isReachableAtTime(1, 2, 1, 2, 1);
  cout << r << endl;

  r = sol.isReachableAtTime(3, 1, 7, 3, 3);
  cout << r << endl;

  r = sol.isReachableAtTime(2, 4, 7, 7, 6);
  cout << r << endl;
}
