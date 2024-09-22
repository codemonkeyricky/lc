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
    string shortestBeautifulSubstring(string s, int k) {

        int n = s.size(), kk = 0;
        vector<int> index;
        for (auto i = 0; i < n; ++i)
            if (s[i] == '1')
                index.push_back(i);

        string rv = s;
        int found = 0;
        for (int i = 0; i <= (int)index.size() - k; ++i) {
            if (index[i + k - 1] - index[i] <= s.size()) {
                found = 1; 
                string ss = s.substr(index[i], index[i + k - 1] - index[i] + 1);
                if (ss.size() < rv.size())
                    rv = ss;
                else if (ss.size() == rv.size() && ss < rv)
                    rv = ss;
            }
        }
        return found ? rv : "";
    }
};

int main() {
    Solution sol;
    string r;

        r = sol.shortestBeautifulSubstring("1111111011111", 12);
    cout << r << endl;

    r = sol.shortestBeautifulSubstring("1100100101011001001", 7);
    cout << r << endl;

    r = sol.shortestBeautifulSubstring("000", 1);
    cout << r << endl;

    r = sol.shortestBeautifulSubstring("1011", 2);
    cout << r << endl;
}