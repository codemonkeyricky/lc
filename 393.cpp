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
    bool validUtf8(vector<int> &data)
    {
        int n = data.size(), i = 0;
        while (i < n)
        {
            int bytes = 0;
            if ((data[i] & 0x80) == 0)
                bytes = 1;
            else if ((data[i] & 0xe0) == 0xc0)
                bytes = 2;
            else if ((data[i] & 0xf0) == 0xe0)
                bytes = 3;
            else if ((data[i] & 0xf8) == 0xf0)
                bytes = 4;
            else
                return false;

            --bytes, ++i;
            if (i + bytes > n)
                return false;
            while (bytes--)
                if ((data[i++] & 0xc0) != 0x80)
                    return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.validUtf8(vector<int>() = {240, 162, 138, 147});
    cout << r << endl;

    r = sol.validUtf8(vector<int>() = {255});
    cout << r << endl;

    r = sol.validUtf8(vector<int>() = {197, 130, 1});
    cout << r << endl;
}