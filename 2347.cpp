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
    string bestHand(vector<int> &r, vector<char> &s)
    {
        if (s[0] == s[1] && s[0] == s[2] && s[0] == s[3] && s[0] == s[4])
            return "Flush";

        sort(begin(r), end(r));
        int maxSame = 1, same = 1;
        for(auto i = 1; i < r.size(); ++i)
        {
            if (r[i] == r[i - 1])
                ++same;
            else 
                same = 1;
            maxSame = max(same, maxSame);
        }

        if (maxSame == 3)
            return "Three of a Kind";
        else if (maxSame == 2)
            return "Pair";

        return "High Card";
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}