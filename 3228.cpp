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
  int maxOperations(string s) {
    int n = s.size();
    int cnt = 0, rv = 0;
    for (auto i = 0; i < n; ++i) {
      if (s[i] == '1') {
        if (i && s[i - 1] == '0')
          rv += cnt;
        ++cnt;
      }
    }

    if (s.back() == '0')
      rv += cnt;

    return rv;
  }
};

int main() {
  Solution sol;
  int r;

  r = sol.maxOperations("00111");
  cout << r << endl;

  r = sol.maxOperations("1001101");
  cout << r << endl;
}