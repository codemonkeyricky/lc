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
    vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l, vector<int> &r)
    {
        vector<bool> rv;
        for (auto k = 0; k < l.size(); ++k)
        {
            auto i = l[k], j = r[k];
            auto q = multiset<int>(begin(nums) + i, begin(nums) + j + 1);
            if(q.size() == 1)
                rv.push_back(true);
            else 
            {
                int d = *next(begin(q)) - *begin(q);
                bool arith = true;
                for (auto it = next(begin(q)); it != end(q) && arith; ++it)
                    if (*it - *prev(it) != d)
                        arith = false;
                rv.push_back(arith);
            }
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}