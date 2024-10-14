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
    bool contains(array<int, 26>& cnt, array<int, 26>& req) {
        for (auto i = 0; i < 26; ++i) {
            if (cnt[i] < req[i])
                return false;
        }
        return true;
    }

  public:
    long long validSubstringCount(string word1, string word2) {

        int n = word1.size();
        array<int, 26> req = {};

        for (auto i = 0; i < word2.size(); ++i)
            ++req[word2[i] - 'a'];

        array<int, 26> cnt = {};
        long long rv = 0;
        for (auto i = 0, j = 0; j < word1.size(); ++j) {
            ++cnt[word1[j] - 'a'];

            while (contains(cnt, req)) {
                --cnt[word1[i++] - 'a'];
            }

            rv += i;
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.validSubstringCount("abcabc", "abc");
    cout << r << endl;

    r = sol.validSubstringCount("bcca", "abc");
    cout << r << endl;
}
