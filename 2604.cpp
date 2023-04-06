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
    int minimumTime(vector<int> &hens, vector<int> &grains)
    {
        sort(begin(hens), end(hens));
        sort(begin(grains), end(grains));

        int l = 0, r = 1e9;
        while (l < r)
        {
            int m = (l + r) / 2;
            int i = 0, j = 0; 
            for (; i < hens.size() && j < grains.size(); ++i)
            {
                if (grains[j] <= hens[i])
                {
                    int jj = j;
                    for (; jj < grains.size(); ++jj)
                    {
                        if (hens[i] >= grains[jj])
                            if (hens[i] - grains[jj] > m)
                                break;
                            else
                                ;
                        else if (((hens[i] - grains[j]) * 2 + grains[jj] - hens[i] > m) 
                               && (hens[i] - grains[j] + (grains[jj] - hens[i]) * 2 > m) )
                            break;
                    }
                    j = jj;
                }
                else 
                {

                    int jj = j;
                    for (; jj < grains.size(); ++jj)
                        if (grains[jj] - hens[i] > m)
                            break;
                    j = jj;
                }
            }

            if (j >= grains.size())
                r = m;
            else 
                l = m + 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumTime(vector<int>() = {0}, vector<int>() = {1000000000});
    cout << r << endl;

    r = sol.minimumTime(vector<int>() = {4, 6, 109, 111, 213, 215}, vector<int>() = {5, 110, 214});
    cout << r << endl;

    r = sol.minimumTime(vector<int>() = {3, 6, 7}, vector<int>() = {2, 4, 7, 9});
    cout << r << endl;
}