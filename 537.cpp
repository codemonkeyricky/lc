#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

class Solution
{
public:
    string complexNumberMultiply(string num1, string num2)
    {
        array<int, 2> n1, n2, n3;
        auto plus = num1.find("+");
        n1 = {stoi(num1.substr(0, plus)), stoi(num1.substr(plus + 1, num1.size() - plus - 1))};

        plus = num2.find("+");
        n2 = {stoi(num2.substr(0, plus)), stoi(num2.substr(plus + 1, num2.size() - plus - 1))};

        n3 = {n1[0] * n2[0] - n1[1] * n2[1], n1[1] * n2[0] + n1[0] * n2[1]};

        return to_string(n3[0]) + "+" + to_string(n3[1]) + "i";
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.complexNumberMultiply("1+1i", "1+1i");
    cout << r << endl;
}