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


// This is the FontInfo's API interface.
// You should not implement it, or speculate about its implementation
class FontInfo {
  public:
    // Return the width of char ch when fontSize is used.
    int getWidth(int fontSize, char ch);
    
    // Return Height of any char when fontSize is used.
    int getHeight(int fontSize)
};

class Solution
{
public:
    int maxFont(string text, int w, int h, vector<int> &fonts, FontInfo fontInfo)
    {
        int n = fonts.size();
        int l = 0, r = n - 1;
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            int width = 0, height = 0;
            for (auto &c : text)
                width += fontInfo.getWidth(fonts[m], c), height = max(height, fontInfo.getHeight(fonts[m]));

            if (height > h || width > w)
                r = m - 1;
            else
                l = m;
        }

        if (l)
            return fonts[l];

        int width = 0, height = 0;
        for (auto &c : text)
            width += fontInfo.getWidth(fonts[0], c), height = max(height, fontInfo.getHeight(fonts[0]));

        return (height > h || width > w) ? -1 : fonts[0];
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}