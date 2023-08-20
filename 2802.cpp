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
    string kthLuckyNumber(int k)
    {
        --k;
        int power_of_two = 2, digit = 0;
        while (k >= power_of_two)
            k -= power_of_two, power_of_two <<= 1, ++digit;
        string s;
        while (digit >= 0)
        {
            if (k & (1 << digit))
                s += "7";
            else
                s += "4";
            --digit;
        }
        return s;
    }
};

int main()
{
    Solution sol;
    string r;

    // r = sol.kthLuckyNumber(1000);
    // cout << r << endl;

    r = sol.kthLuckyNumber(10);
    cout << r << endl;

    r = sol.kthLuckyNumber(4);
    cout << r << endl;
}