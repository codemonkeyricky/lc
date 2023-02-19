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
    vector<string> ipToCIDR(string ip, int n)
    {
        long ips = 0x100000000, ipe = 0, k = 3;
        string s;
        for (auto i = 0; i <= ip.size(); ++i)
            if (i >= ip.size() || ip[i] == '.')
                ips += stoi(s) << (k-- * 8), s.clear();
            else
                s += ip[i];
        ipe = ips + n;
        vector<array<long, 2>> rv;
        while (ips < ipe)
        {
            long p = ips & ~(ips - 1);
            while (ips + p > ipe)
                p >>= 1;
            long bits = __builtin_popcount(--p);
            rv.push_back({ips, bits});
            ips += (p + 1);
        }

        vector<string> rv2;
        for (auto [ip, mask] : rv)
        {
            int o1 = (ip & 0xFF000000) >> 24;
            int o2 = (ip & 0x00FF0000) >> 16;
            int o3 = (ip & 0x0000FF00) >> 8;
            int o4 = (ip & 0x000000FF) >> 0;

            rv2.push_back(to_string(o1) + "." + to_string(o2) + "." + to_string(o3) + "." + to_string(o4) + "/" + to_string(32 - mask));
        }

        return rv2;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.ipToCIDR("0.0.0.0", 1);

    sol.ipToCIDR("255.0.0.7", 10);
}