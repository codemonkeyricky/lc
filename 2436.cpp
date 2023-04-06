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
    int minimumSplits(vector<int>& nums) {
        int rv = 1; 
        for(auto i = 0, c = nums[0]; i < nums.size(); ++i)
        {
            c = __gcd(c, nums[i]);
            if (c == 1)
                ++rv, c = nums[i];
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumSplits(vector<int>() = {22951677, 38066196, 48142542, 55419903, 3918579, 16793910, 55419903, 21832083, 2877424, 784752, 9155440, 22757808, 20665136, 5231680, 5493264, 20403552, 23019392, 23280976, 1046336, 6801184, 20403552, 25635232, 24065728, 23804144, 523168, 2615840, 17787712, 13259792, 11365536, 39305812, 32675916, 22062750, 13429500, 40288500, 53718000, 45084750, 13429500, 34533000, 60432750, 58514250, 13429500, 42207000, 22062750, 57015600, 29220495, 70556805, 9265035, 49888650, 12115815, 18530070, 20668155, 64142550, 47750565, 45612480, 42049005, 69844110, 39198225, 9977730, 29220495, 65567940, 30645885, 43714517, 24996609, 11760765, 10764090, 1594680, 13554780, 19335495, 11561430, 15858920, 11894190, 20616596, 39647300, 6149138, 3482042});
    cout << r << endl;
}