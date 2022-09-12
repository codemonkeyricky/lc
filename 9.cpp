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
    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;
        
        long long l = 1;
        while (x / l)
            l *= 10;
        l /= 10;

        while (l)
        {
            if (x / l != x % 10)
                return false;
            
            x %= l;
            x /= 10;
            l /= 100;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isPalindrome(121);
    cout << r << endl;
}