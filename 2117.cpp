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
    string abbreviateProduct(int left, int right)
    {
        long long suff = 1, c = 0, total = 0, max_suff = 100000000000;
        double pref = 1.0;
        for (int i = left; i <= right; ++i)
        {
            pref *= i;
            suff *= i;
            while (pref >= 100000)
            {
                pref /= 10;
                total = total == 0 ? 6 : total + 1;
            }
            while (suff % 10 == 0)
            {
                suff /= 10;
                ++c;
            }
            suff %= max_suff;
        }
        string s = to_string(suff);
        return to_string((int)pref) + (total - c <= 10 ? "" : "...") + (total - c < 5 ? "" : s.substr(s.size() - min(5LL, total - c - 5))) + "e" + to_string(c);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}