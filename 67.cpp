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
    string addBinary(string a, string b)
    {
        reverse(begin(a), end(a));
        reverse(begin(b), end(b));

        int c = 0;
        string rv;
        for (auto i = 0, k = 0; i < a.size() || i < b.size(); ++i)
        {
            k = c + (i < a.size() ? a[i] - '0' : 0) + (i < b.size() ? b[i] - '0' : 0);
            c = k / 2;
            rv.push_back((k % 2) + '0');
        }

        if (c)
            rv += string(1, '1');

        reverse(begin(rv), end(rv));
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.addBinary("1", "111");
    cout << r << endl;
}