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
    int dfs(string& s1, string& s2, string& s3, int i, int j, int k) {

        if (k < 0)
            return true;

        int rv = 0;
        if (i >= 0 && s1[i] == s3[k])
            if (dfs(s1, s2, s3, i - 1, j, k - 1))
                return true;

        if (j >= 0 && s2[j] == s3[k])
            if (dfs(s1, s2, s3, i, j - 1, k - 1))
                return true;

        return false;
    }

  public:
    bool isInterleave(string s1, string s2, string s3) {

        return dfs(s1, s2, s3, s1.size() - 1, s2.size() - 1, s3.size() - 1);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.isInterleave("aabcc", "dbbca", "aadbbbaccc");
    cout << r << endl;

    r = sol.isInterleave("aabcc", "dbbca", "aabbcbcac");
    cout << r << endl;
}
