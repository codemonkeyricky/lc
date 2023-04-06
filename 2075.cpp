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
    string decodeCiphertext(string encoded, int rows)
    {
        int m = rows, n = encoded.size() / rows;
        string rv;
        for (auto k = 0, i = 0, j = k; k < n; ++k, i = 0, j = k)
            while (i * n + j < encoded.size())
                rv.push_back(encoded[i++ * n + j++]);

        while (rv.back() == ' ')
            rv.pop_back();

        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.decodeCiphertext("ch   ie   pr", 3);
    cout << r << endl;

    r = sol.decodeCiphertext("iveo    eed   l te   olc", 4);
    cout << r << endl;
}