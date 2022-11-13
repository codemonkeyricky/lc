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
    int sum(long long n)
    {
        int rv = 0;
        while (n)
            rv += n % 10, n /= 10;
        return rv;
    }

public:
    long long makeIntegerBeautiful(long long n, int target)
    {
        long long m = 1;
        auto nn = n;
        while (sum(m) < sum(n))
        {
            n = nn;
            n += m - 1;
            n -= n % m;
            if (sum(n) <= target)
                return n - nn;
            m *= 10;
        }
        return m - nn;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.makeIntegerBeautiful(20, 2);
    cout << r << endl;

    r = sol.makeIntegerBeautiful(8, 2);
    cout << r << endl;

    r = sol.makeIntegerBeautiful(467, 6);
    cout << r << endl;

    r = sol.makeIntegerBeautiful(16, 6);
    cout << r << endl;
}