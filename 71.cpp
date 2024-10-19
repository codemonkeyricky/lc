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
  public:
    string simplifyPath(string path) {

        vector<string> tokens;
        string token;

        for (auto s : path) {
            if (s == '/') {
                if (token.size()) {
                    if (token == "..") {
                        if (tokens.size())
                            tokens.pop_back();
                    } else if (token == ".")
                        ;
                    else
                        tokens.push_back(token);
                }
                token.clear();
            } else {
                token += string(1, s);
            }
        }

        if (token.size()) {
            if (token == "..") {
                if (tokens.size())
                    tokens.pop_back();
            } else if (token == ".")
                ;
            else
                tokens.push_back(token);
        }

        string rv;
        for (auto t : tokens) {
            rv += "/" + t;
        }
        return rv.empty() ? "/" : rv;
    }
};

int main() {
    Solution sol;
    string r;

    r = sol.simplifyPath("/a//b////c/d//././/..");
    cout << r << endl;

    r = sol.simplifyPath("/../");
    cout << r << endl;

    r = sol.simplifyPath("/home/user/Documents/../Pictures");
    cout << r << endl;

    r = sol.simplifyPath("/.../a/../b/c/../d/./");
    cout << r << endl;
}
