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
    string fractionAddition(string expr)
    {
        vector<array<int, 2>> frac;
        int i = 0, n = expr.size();
        while (i < n)
        {
            string num;
            while (expr[i] != '/')
                num += expr[i++];
            ++i;

            string denom;
            while (i < n && expr[i] != '+' && expr[i] != '-')
                denom += expr[i++];

            frac.push_back({stoi(num), stoi(denom)});
        }

        int lcm = 1;
        for (auto &f : frac)
            lcm = std::lcm(lcm, f[1]);

        for (auto &f : frac)
        {
            auto m = lcm / f[1];
            f[0] *= m;
            f[1] *= m;
        }

        int num_sum = 0;
        for (auto &f : frac)
            num_sum += f[0];

        if (num_sum == 0)
            return "0/1";

        int gcd = std::gcd(num_sum, frac[0][1]);
        return to_string(num_sum / gcd) + "/" + to_string(frac[0][1] / gcd);
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.fractionAddition("1/3-1/2");
    cout << r << endl;

    r = sol.fractionAddition("-1/2+1/2+1/3");
    cout << r << endl;

    r = sol.fractionAddition("-1/2+1/2");
    cout << r << endl;
}