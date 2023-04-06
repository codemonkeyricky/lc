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
    int divisorSubstrings(int num, int k)
    {

        int copy = num;
        int p = 1;
        int n = 0;
        int rv = 0;
        --k;
        while (num)
        {
            n += (num % 10) * p;
            if (!k && n && copy % n == 0)
                ++rv;

            if (k)
                --k, p *= 10;
            else
                n /= 10;

            num /= 10;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.divisorSubstrings(30003, 3);
    cout << r << endl;

    r = sol.divisorSubstrings(430043, 2);
    cout << r << endl;

    r = sol.divisorSubstrings(240, 2);
    cout << r << endl;
}