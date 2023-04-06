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
    long long countExcellentPairs(vector<int> &nums, int k)
    {
        vector<int> bits(33);

        sort(begin(nums), end(nums));
        nums.erase(unique(nums.begin(), nums.end()), nums.end());

        for (auto &n : nums)
            ++bits[__builtin_popcount(n)];

        vector<int> sum(61);
        for (int i = 32; i >= 0; --i)
            sum[i] = bits[i] + (i < 32 ? sum[i + 1] : 0);

        long long rv = 0;
        for (auto &n : nums)
            rv += sum[max(k - __builtin_popcount(n), 0)];
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countExcellentPairs(vector<int>() = {423436147, 29690092, 724837828, 339900252, 819138876, 559797269, 337577818, 347372617, 568172510, 434046210, 233465903, 73777015, 995100887, 952551841, 314703814, 588503612, 5824363, 105686599, 5167368, 154358365, 497653021, 450975800, 431388582, 607991479, 856148544, 982787927, 513430676, 918344731, 98092726, 690894469, 396191705, 848402861, 593468334, 563155911, 715586102, 739434236, 387304407, 927581316, 779272764, 558853665, 215920106, 631709145, 726054493, 415057810, 708860839, 401596916, 795418594, 462963799, 835785708, 670198432, 171214014, 162179684, 27901422, 717744871, 603604788, 664478320, 915525044, 818068724, 564705733, 490294265, 804021123, 688892990, 741612165, 590640255, 535167444, 228105610, 197887678, 963803394, 698521654, 794863135, 712203903, 16780599, 583378338, 927863644, 628601885, 878322079, 632547981, 426926648}, 55);
    cout << r << endl;

    r = sol.countExcellentPairs(vector<int>() = {1, 2, 3, 1, 536870911}, 3);
    cout << r << endl;

    r = sol.countExcellentPairs(vector<int>() = {1, 2, 3, 1}, 3);
    cout << r << endl;
}