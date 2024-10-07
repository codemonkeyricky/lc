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
    int longest(string& word, int i, int j, int k, int l) {
        int rv = 0;
        for (; i < j && k < l; ++i, ++k, ++rv)
            if (word[i] != word[k])
                break;
        return rv;
    }

  public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        int rv = (n + k - 1) / k;
        for (int i = n - 1; i >= k; --i) {
            // Find nearest k increment
            int kk = i / k * k;
            // Find longest match
            int l = longest(word, 0, n, kk, n);
            if (l == n - kk)
                rv = min(rv, (n - l) / k);
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumTimeToInitialState("aa", 1);
    cout << r << endl;

    // r = sol.minimumTimeToInitialState("ababa", 2);
    // cout << r << endl;

    // r = sol.minimumTimeToInitialState("abacaba", 3);
    // cout << r << endl;

    // r = sol.minimumTimeToInitialState("abacaba", 4);
    // cout << r << endl;

    r = sol.minimumTimeToInitialState("abcbabcd", 2);
    cout << r << endl;
}
