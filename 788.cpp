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
    int rotate(int n)
    {
        string rv;
        int nn = n;
        while (n)
        {
            switch (n % 10)
            {
                case 0: rv.push_back(0 + '0'); break;
                case 1: rv.push_back(1 + '0'); break;
                case 2: rv.push_back(5 + '0'); break;
                case 3: return nn; 
                case 4: return nn; 
                case 5: rv.push_back(2 + '0'); break;
                case 6: rv.push_back(9 + '0'); break;
                case 7: return nn;
                case 8: rv.push_back(8 + '0'); break;
                case 9: rv.push_back(6 + '0'); break;
            }
            n /= 10;
        }
        reverse(begin(rv), end(rv));
        return stoi(rv);
    }

public:
    int rotatedDigits(int n)
    {
        int rv = 0;
        for (auto i = 1; i <= n; ++i)
            if (rotate(i) != i)
                ++rv;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.rotatedDigits(10);
    cout << r << endl;
}