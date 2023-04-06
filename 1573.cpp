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
    int numWays(string s)
    {
        long n = s.size();

        auto total = accumulate(begin(s), end(s), 0, [](int sum, const char &c)
                                { return sum + (c == '1'); });
        if (total % 3)
            return 0;

        long l = 0, r = 0;
        int target = total / 3;
        int sum = 0;
        for (auto &c : s)
        {
            sum += c == '1';
            if (sum == target)
                ++l;
            else if (sum == target * 2)
                ++r;
        }
        if (total)
            return (l * r) % 1000000007;
        else
            return ((n - 1) * (n - 2) / 2) % 1000000007;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numWays("10101");
    cout << r << endl;
}