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
    int evalRPN(vector<string>& tokens) {
        vector<string> stack;
        for (auto& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                auto b = stoi(stack.back());
                stack.pop_back();
                auto a = stoi(stack.back());
                stack.pop_back();

                int c;
                if (token == "+")
                    c = a + b;
                else if (token == "-")
                    c = a - b;
                else if (token == "*")
                    c = a * b;
                else if (token == "/")
                    c = a / b;
                stack.push_back(to_string(c));
            } else {
                stack.push_back(token);
            }
        }
        return stoi(stack.back());
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.evalRPN(vector<string>() = {"4", "13", "5", "/", "+"});
    cout << r << endl;

    r = sol.evalRPN(vector<string>() = {"2", "1", "+", "3", "*"});
    cout << r << endl;
}
