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
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int> &energy, vector<int> &experience)
    {
        int req_eng = accumulate(begin(energy), end(energy), 0);

        int n = energy.size(), l = 0, r = 1e9;
        while (l < r)
        {
            auto m = (l + r) / 2;
            auto curr = m;
            auto pass = true;
            for (auto i = 0; i < n && pass; ++i)
                if (curr <= experience[i])
                    pass = false;
                else 
                    curr += experience[i];
            if (pass)
                r = m;
            else
                l = m + 1;
        }

        return max(req_eng - initialEnergy + 1, 0) + max(l - initialExperience, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minNumberOfHours(30, 78, vector<int>() = {24, 91, 63, 38, 31, 63, 22, 35, 91, 54, 88, 46, 80, 14, 12, 19, 57, 92}, vector<int>() = {18, 43, 36, 88, 84, 21, 82, 54, 61, 80, 68, 54, 75, 27, 99, 14, 86, 95});
    cout << r << endl;

    r = sol.minNumberOfHours(5, 3, vector<int>() = {1, 4, 3, 2}, vector<int>() = {2, 6, 3, 1});
    cout << r << endl;
}