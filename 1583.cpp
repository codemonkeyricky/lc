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
    int unhappyFriends(int n, vector<vector<int>> &pref, vector<vector<int>> &pairs)
    {
        unordered_map<int, int> pairing;
        for(auto & p : pairs)
        {
            auto x = p[0], y = p[1];
            pairing[x] = y;
            pairing[y] = x;
        }

        bitset<501> unhappy;
        for (auto &p : pairs)
        {
            auto x = p[0], y = p[1];
            for (auto k = 0; k < 2; ++k)
            {
                for (auto &u : pref[x])
                {
                    if (u == y)
                        break;
                    for (auto &v : pref[u])
                    {
                        if (v == pairing[u])
                            break;
                        if (v == x)
                            unhappy[v] = unhappy[x] = true;
                    }
                }
                swap(x, y);
            }
        }

        return unhappy.count();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.unhappyFriends(4, vector<vector<int>>() = {{1, 2, 3}, {3, 2, 0}, {3, 1, 0}, {1, 2, 0}}, vector<vector<int>>() = {{0, 1}, {2, 3}});
    cout << r << endl;
}