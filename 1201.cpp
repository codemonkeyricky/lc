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

typedef long long ll;
class Solution
{
public:
    ll lcm(ll a, ll b)
    {
        return a * b / __gcd(a, b);
    }

    int nthUglyNumber(int n, int a, int b, int c)
    {
        ll N = (ll)n, A = ll(a), B = ll(b), C = ll(c);
        ll l = 1, r = 2000000000, m;

        while (l < r)
        {
            m = (l + r) / 2;
            ll k = 0;
            k += m / A;
            k += m / B;
            k += m / C;
            k -= m / lcm(A, B);
            k -= m / lcm(B, C);
            k -= m / lcm(C, A);
            k += m / lcm(a, lcm(b, c));

            if (k >= N)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}