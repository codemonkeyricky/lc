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
    int numberOfSubstrings(const string& s) {
        int rv = 0;
        for (int z = 0; z + z * z <= s.size(); ++z) {
            int cnt[2] = {}, p = 0, old_rv = rv;
            for (int i = 0, j = 0; i < s.size(); ++i) {
                ++cnt[s[i] == '1'];
                while (cnt[0] > z)
                    --cnt[s[j++] == '1'];
                if (cnt[0] == z && cnt[1] && cnt[1] >= z * z) {
                    for (p = max(p, j); p < i && s[p] == '1'; ++p)
                        ;
                    rv += 1 + min(p - j, cnt[1] - z * z);
                }
            }
            if (rv == old_rv)
                break;
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.numberOfSubstrings("10");
    cout << r << endl;

    r = sol.numberOfSubstrings("1011");
    cout << r << endl;

    r = sol.numberOfSubstrings("00011");
    cout << r << endl;
}