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
    string smallestGoodBase(string s)
    {
        auto n = stoll(s);
        for (auto i = 2; i < 15; ++i)
        {
            long long k = 0, p = 1;
            while (k < n)
            {
                k += p; 
                p *= i;
            }
            if (k == n)
                return to_string(i);
        }
        return "";
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.smallestGoodBase("1000000000000000000");
    cout << r << endl;

    r = sol.smallestGoodBase("4681");
    cout << r << endl;

    r = sol.smallestGoodBase("13");
    cout << r << endl;
}