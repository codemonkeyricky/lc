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
    int sumFourDivisors(vector<int> &nums)
    {
        int rv = 0;
        for (auto &n : nums)
        {
            unordered_set<int> div;
            div.insert(1), div.insert(n);
            for (auto i = 2; i * i <= n; ++i)
            {
                int f = i;
                while (n % i == 0)
                    div.insert(f), n /= i, f *= i;
            }
            if (n > 1)
                div.insert(n);

            if (div.size() == 4)
            {
                int r = 0;
                for (auto &d : div)
                    r += d;
                rv += r;
            }
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sumFourDivisors(vector<int>() = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << r << endl;

    r = sol.sumFourDivisors(vector<int>() = {21, 4, 7});
    cout << r << endl;
}