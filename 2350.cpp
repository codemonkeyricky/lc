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
    int shortestSequence(vector<int> &rolls, int k)
    {
        unordered_set<int> set;
        int rv = 0;
        for (auto &n : rolls)
        {
            set.insert(n);
            if (set.size() == k)
                set.clear(), ++rv;
        }
        return 1 + rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.shortestSequence(vector<int>() = {4, 2, 1, 2, 3, 3, 2, 4, 1}, 4);
    cout << r << endl;
}

// int n = rolls.size();
//         int m = k;
//         vector<int> perm = {0};
//         while (m < n)
//             perm.push_back(m), m *= k;

//         int l = 1, r = rolls.size() - 1;
//         bitset<100001> bits;
//         while (l < r)
//         {
//             auto k = (l + r + 1) / 2; 
//             int mul = 1, sum = 0;
//             for (auto i = 0, j = 0; j < rolls.size(); ++j)
//             {
//                 if (j < k)
//                     mul *= k;
//                 else
//                     sum *= k, sum -= mul * rolls[i++];
//                 sum += rolls[j];

//                 if (j >= k)
//                     bits[sum] = true;
//             }

//             if (bits.count() == perm[m])
//                 l = m;
//             else
//                 r = m - 1;
//         }
//         return l;