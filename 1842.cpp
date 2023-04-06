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
    string nextPalindrome(string num)
    {
        string s = num.substr(0, num.size() / 2);

        int i = s.size() - 2;
        while (i >= 0 && s[i + 1] <= s[i])
            --i;

        if (i < 0)
            return "";

        int j = s.size() - 1;
        while (s[j] <= s[i])
            --j;
        swap(s[i], s[j]);
        reverse(begin(s) + i + 1, end(s));

        auto s2 = s;
        reverse(begin(s2), end(s2));

        return s + (num.size() % 2 ? string(1, num[num.size() / 2]) : "") + s2;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.nextPalindrome("23143034132");
    cout << r << endl;

    r = sol.nextPalindrome("45544554");
    cout << r << endl;
}