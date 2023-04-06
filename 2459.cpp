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
    int permute(vector<int> npos, int s)
    {
        int rv = 0, next = 1, ni, n = npos.size();
        while (next < n)
        {
            if (npos[0] == s * (n - 1))
            {
                while (npos[next] == next - s)
                    if (++next == n)
                        return rv;
                ni = next;
            }
            else
                ni = npos[0] + s;

            swap(npos[0], npos[ni]);

            ++rv;
        }
        return rv;
    }

public:
    int sortArray(vector<int> &nums)
    {
        int n = nums.size();

        // note that 'npos' is passed by value INTENTIONALLY,
        // because it calls copy constructor
        // if we pass it by referece then the same 'npos'
        // will be used for both s=0 and s=1

        vector<int> npos(n);
        for (int i = 0; i < n; ++i)
            npos[nums[i]] = i;

        return min(permute(npos, 0), permute(npos, 1));
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sortArray(vector<int>() = {4, 1, 2, 3, 0});
    cout << r << endl;

    // r = sol.sortArray(vector<int>() = {1, 2, 5, 4, 3, 6, 0});
    // cout << r << endl;

    // r = sol.sortArray(vector<int>() = {1, 2, 3, 4, 0});
    // cout << r << endl;

    // r = sol.sortArray(vector<int>() = {3, 2, 1, 6, 7, 4, 5, 0});
    // cout << r << endl;

    // r = sol.sortArray(vector<int>() = {4, 2, 0, 3, 1});
    // cout << r << endl;
}