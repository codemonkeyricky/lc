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
  int dfs(map<int, vector<int>>& al, int k, set<int>& visited, int* same) {
    vector<int> subtree;
    visited.insert(k);
    for (auto& n : al[k])
      if (!visited.count(n))
        subtree.push_back(dfs(al, n, visited, same));

    int same_size = 1;
    for (int i = 0; i < (int)subtree.size() - 1; ++i)
      if (subtree[i] != subtree[i + 1])
        same_size = 0;

    int total_nodes = 1;
    for (auto& s : subtree)
      total_nodes += s;

    visited.erase(k);

    *same += same_size;

    return total_nodes;
  }

 public:
  int countGoodNodes(vector<vector<int>>& edges) {
    int n = edges.size();
    map<int, vector<int>> al;

    for (auto& e : edges)
      al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);

    set<int> visited;
    int rv = 0;
    dfs(al, 0, visited, &rv);
    return rv;
  }
};

int main() {
  Solution sol;
  int r;

  r = sol.countGoodNodes(
      vector<vector<int>>() = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}});
  cout << r << endl;
}