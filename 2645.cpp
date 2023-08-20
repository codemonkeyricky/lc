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
    int addMinimum(string word)
    {
        int n = word.size(), rv = 0, index = 0;
        for (auto i = 0; i < n; ++i)
        {
            int k = word[i] - 'a';
            if (k == index)
                // match
                index = (index + 1) % 3;
            else 
            {
                if (index == 0)
                {
                    if (k == 1)
                        // expect a but got b
                        ++rv, index = 2;
                    else if (k == 2)
                        // expect a but got c
                        ++ ++rv, index = 0;
                }
                else if (index == 1)
                {
                    if (k == 0)
                        // expect b but got a
                        ++ ++rv, index = 1;
                    else if (k == 2)
                        // expect b but got c
                        ++rv, index = 0;
                }
                else
                {
                    if (k == 0)
                        // expect c but got a
                        ++rv, index = 1;
                    else if (k == 1)
                        // expect c but got b
                        ++ ++rv, index = 2;
                }
            }
        }

        if (index == 0)
            ;
        else if(index == 1)
            ++ ++rv;
        else if(index == 2)
            ++rv; 

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.addMinimum("aaaabb");
    cout << r << endl;
}