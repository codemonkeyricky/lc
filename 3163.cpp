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
    string dfs(string& word, int k) {
        int n = word.size();

        if (k >= n)
            return "";

        char c = word[k];
        int cnt = 0;
        for (auto i = 0; i <= 9 && k + i <= n; ++i) {
            if (i < 9 && k + i < n && word[k + i] == c)
                ++cnt;
            else {
                return to_string(cnt) + string(1, c) + dfs(word, k + i);
            }
        }
        return "";
    }

  public:
    string compressedString(string word) { return dfs(word, 0); }
};

int main() {
    Solution sol;
    string r;

    r = sol.compressedString("aaaaaaaaaaaaaabb");
    cout << r << endl;

    r = sol.compressedString("abcde");
    cout << r << endl;
}
