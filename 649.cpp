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
    string predictPartyVictory(string senate)
    {
        int n = senate.size();
        set<int> rad, dire;
        for (auto i = 0; i < n; ++i)
            if (senate[i] == 'R')
                rad.insert(i);
            else
                dire.insert(i);

        int k = 0;
        while (rad.size() && dire.size())
        {
            auto rit = rad.lower_bound(k);
            auto dit = dire.lower_bound(k);
            if (k <= *rbegin(rad) && k <= *rbegin(dire))
            {
                if (*rit < *dit)
                    dire.erase(dit), k = *rit + 1;
                else
                    rad.erase(rit), k = *dit + 1;
            }
            else if (k <= *rbegin(rad))
                dire.erase(begin(dire)), k = *rit + 1;
            else if (k <= *rbegin(dire))
                rad.erase(begin(rad)), k = *dit + 1;
            else
                k = 0;
        }

        return dire.empty() ? "Radiant" : "Dire";
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.predictPartyVictory("DRRDRDRDRDDRDRDR");
    cout << r << endl;

    r = sol.predictPartyVictory("DDRRR");
    cout << r << endl;
}