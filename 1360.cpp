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
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysBetweenDates(string d1, string d2)
    {
        return abs(daysFrom1971(d1) - daysFrom1971(d2));
    }
    bool isLeap(int y)
    {
        return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
    }
    int daysFrom1971(string dt)
    {
        int y = stoi(dt.substr(0, 4)), m = stoi(dt.substr(5, 2)), d = stoi(dt.substr(8));
        for (int iy = 1971; iy < y; ++iy)
            d += isLeap(iy) ? 366 : 365;
        return d + (m > 2 && isLeap(y)) + accumulate(begin(days), begin(days) + m - 1, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}