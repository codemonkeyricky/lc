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
    int numberOfRounds(string loginTime, string logoutTime)
    {
        int login = stoi(loginTime.substr(0, 2)) * 60 + stoi(loginTime.substr(3));
        int logout = stoi(logoutTime.substr(0, 2)) * 60 + stoi(logoutTime.substr(3));

        if (logout < login)
            logout += 1440;

        int rv = 0;
        for (auto i = login; i <= logout; ++i)
            if (i % 15 == 0)
                ++rv;
        return max(0, rv - 1);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.numberOfRounds("09:31", "10:14");
    cout << r << endl;
}