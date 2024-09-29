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

    array<int, 26> get_chars(string& s, int k, int l) {
        array<int, 26> rv = {};
        for (auto i = k; i < k + l; ++i)
            ++rv[s[i] - 'a'];
        return rv;
    }

  public:
    int minAnagramLength(string s) {
        int n = s.size();
        for (auto i = 1; i * 2 <= n; ++i) {
            if (n % i == 0) {
                auto ref = get_chars(s, 0, i);
                bool anagram = true;
                for (auto j = i; j < n && anagram; j += i) {
                    if (ref != get_chars(s, j, i))
                        anagram = false;
                }

                if (anagram)
                    return i;
            }
        }
        return n;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minAnagramLength("aabbabab");
    cout << r << endl;

    r = sol.minAnagramLength("cdef");
    cout << r << endl;

    r = sol.minAnagramLength("abba");
    cout << r << endl;
}
