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
    int countPairs(vector<int> &deliciousness)
    {
        sort(begin(deliciousness), end(deliciousness));

        vector<int> pow2;
        int p = 1;
        for (auto i = 1; i <= 22; ++i, p *= 2)
            pow2.push_back(p);

        map<int, long> food;
        for (auto &d : deliciousness)
            ++food[d];

        const int MOD = 1e9 + 7;
        long rv = 0;
        for (auto &f : food)
            for (auto &pow : pow2)
                if (f.first <= pow - f.first)
                    if (pow - f.first == f.first)
                        rv = (rv + f.second * (f.second - 1) / 2) % MOD;
                    else if (food.count(pow - f.first))
                        rv = (rv + f.second * food[pow - f.first]) % MOD;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPairs(vector<int>() = {1048576, 1048576});
    cout << r << endl;

    r = sol.countPairs(vector<int>() = {149, 107, 1, 63, 0, 1, 6867, 1325, 5611, 2581, 39, 89, 46, 18, 12, 20, 22, 234});
    cout << r << endl;

    r = sol.countPairs(vector<int>() = {1, 3, 5, 7, 9});
    cout << r << endl;

    r = sol.countPairs(vector<int>() = {1, 1, 1, 3, 3, 3, 7});
    cout << r << endl;
}