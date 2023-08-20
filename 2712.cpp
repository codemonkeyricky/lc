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
    long long minimumCost(string s)
    {
        int n = s.size();
        vector<array<long, 2>> backward(n), forward(n);

        forward[0][0] = s[0] == '1';
        forward[0][1] = s[0] == '0';
        for (auto i = 1; i < n; ++i)
            if (s[i] == '0')
            {
                forward[i][0] = min(forward[i - 1][0],              // 000... + 0, OR
                                    forward[i - 1][1] + i);         // flip(111...) + 0
                forward[i][1] = min(forward[i - 1][0] + i + 1,      // flip(000.. + 0), OR
                                    (forward[i - 1][1] + i) + i + 1); // flip( flip(111...) + 0)
            }
            else // s[i] == '1'
            {
                forward[i][1] = min(forward[i - 1][1],         // 111... + 1, OR
                                    forward[i - 1][0] + i);    // flip(000...) + 1
                forward[i][0] = min(forward[i - 1][1] + i + 1, // flip(111... + 1)
                                    (forward[i - 1][0] + i) + i + 1); // flip(flip(000) + 1)
            }

        backward[n - 1][0] = s[n - 1] == '1';
        backward[n - 1][1] = s[n - 1] == '0';
        for (int i = n - 2; i >= 0; --i)
            if (s[i] == '0')
            {
                backward[i][0] = min(backward[i + 1][0],                        // 000... + 0, OR
                                     backward[i + 1][1] + n - i + 1);           // flip(111...) + 0
                backward[i][1] = min(backward[i + 1][0] + n - i,                // flip(000.. + 0), OR
                                     (backward[i + 1][1] + n - i + 1) + n - i); // flip( flip(111...) + 0)
            }
            else // s[i] == '1'
            {
                backward[i][1] = min(backward[i + 1][1],                        // 111... + 1, OR
                                     backward[i + 1][0] + n - i + 1);           // flip(000...) + 1
                backward[i][0] = min(backward[i + 1][1] + n - i,                // flip(111... + 1)
                                     (backward[i + 1][0] + n - i + 1) + n - i); // flip(flip(000) + 1)
            }

        long rv = 1e9;
        rv = min(backward[0][0], backward[0][1]);
        for (auto i = 1; i < n; ++i)
            rv = min({rv, forward[i - 1][0] + backward[i][0], forward[i - 1][1] + backward[i][1]});

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumCost("010101");
    cout << r << endl;

    r = sol.minimumCost("0011");
    cout << r << endl;
}