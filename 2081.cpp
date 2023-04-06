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
    vector<long long> mirror1{0}, mirror2{0};
    long long isMirror(long long num, int base)
    {
        long long mul = 1;
        while (mul * base <= num)
            mul *= base;
        for (; num; mul /= base * base)
        {
            if (num / mul != num % base)
                return false;
            num = (num - (num / mul) * mul - num % base) / base;
        }
        return true;
    }
    long long generate(int dig, int n, int k, long long first_mul)
    {
        vector<long long> mirror;
        long long res = 0;
        for (int i = 0; n > 0 && i < 10; ++i)
            for (int j = 0; n > 0 && j < mirror1.size(); ++j)
            {
                mirror.push_back(first_mul * i + mirror1[j] * 10 + i);
                if (i != 0 && isMirror(mirror.back(), k))
                {
                    res += mirror.back();
                    --n;
                }
            }
        swap(mirror1, mirror2);
        swap(mirror2, mirror);
        return res + (n == 0 ? 0 : generate(dig + 1, n, k, first_mul * 10));
    }

public:
    long long kMirror(int k, int n)
    {
        long long res = 0;
        for (int i = 1; n > 0 && i < 10; ++i)
        {
            mirror2.push_back(i);
            if (isMirror(i, k))
            {
                res += i;
                --n;
            }
        }
        return res + generate(2, n, k, 10);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.kMirror(3, 7);
    cout << r << endl;

    r = sol.kMirror(2, 5);
    cout << r << endl;
}