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
    int nthSuperUglyNumber(int n, vector<int> &primes)
    {
        int p = primes.size();
        priority_queue<array<long long, 2>, vector<array<long long, 2>>, greater<array<long long, 2>>> pq;
        vector<int> index(p, 1);

        for (int i = 0; i < p; i++)
            pq.push({primes[i], i});

        vector<long long> ugly(n + 1, 0);
        ugly[1] = 1;
        int k = 2;

        while (k <= n)
        {
            ugly[k] = pq.top()[0];
            while (pq.size() && ugly[k] == pq.top()[0])
            {
                /*
                 *  All primes point to the beginning of nums.  As we populate
                 *  the answer array, advance the index to the answer array
                 *  current prime points to.
                 */

                auto [num, pindex] = pq.top();
                pq.pop();
                ++index[pindex];
                num = ugly[index[pindex]] * primes[pindex];
                pq.push({num, pindex});
            }
            ++k;
        }

        return ugly[n];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.nthSuperUglyNumber(35, vector<int>() = {2, 3, 11, 13, 17, 23, 29, 31, 37, 47});
    cout << r << endl;

    r = sol.nthSuperUglyNumber(3, vector<int>() = {2});
    cout << r << endl;

    r = sol.nthSuperUglyNumber(2, vector<int>() = {2});
    cout << r << endl;

    r = sol.nthSuperUglyNumber(12, vector<int>() = {2, 7, 13, 19});
    cout << r << endl;
}