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
    bool isBeautiful(string &num, int kk, int ph, int sum)
    {
        int nn = stoi(num);
        if (nn < kk)
            return false;

        if (ph)
            return false;

        if (sum == 0)
            return false;

        int n = num.size(), ones = 0, tens = 0;
        ones = num[n - 1] - '0';
        if (n > 1)
            tens = num[n - 2] - '0';

        switch (kk)
        {
            case 1:
                return true;
            case 2:
                return ones % 2 == 0;
            case 3:
                return sum % 3 == 0;
            case 4:
                return (tens * 2 + ones) % 4 == 0;
            case 5:
                return ones % 5 == 0;
            case 6:
                return (ones % 2 == 0) && (sum % 3 == 0);
            case 7:
                return (sum + ones * 4) % 7 == 0;
            case 8:
                return (sum * 2 - ones) % 8 == 0;
            case 9:
                return sum % 9 == 0;
            case 10:
                return ones == 0;
            case 11:
                return (sum - 2 * ones) % 11 == 0;
            case 12:
                return (sum * 2 - ones * 2) % 12 == 0;
            case 13:
                return (sum + ones * 3) % 13 == 0;
            case 14:
                return (sum * 2 - ones - tens) % 14 == 0;
            case 15:
                return (sum % 3 == 0) && (ones % 5 == 0);
            case 16:
                return (sum * 4 - ones * 3 - tens * 3) % 16 == 0;
            case 17:
                return (sum - ones * 6) % 17 == 0;
            case 18:
                return (ones % 2 == 0) && (sum % 9) == 0;
            case 19:
                return (sum + ones * 3 + tens * 3) % 19 == 0;
            case 20:
                return (ones == 0) && (tens % 2 == 0);
        }
        return false; 
    }

    int dfs(string &num, string curr, int kk, int k, int ceil, int ph, int sum)
    {
        int n = num.size();
        if(k >= n)
            return isBeautiful(curr, kk, ph, sum);

        int rv = 0;
        for (int i = ceil ? num[k] - '0' : 9; i >= 0; --i)
            rv += dfs(num, curr + string(1, i + '0'), kk, k + 1, ceil && i == num[k] - '0', (sum || i) ? ph + (i % 2 ? 1 : -1) : 0, sum + i);
        return rv;
    }

public:
    int numberOfBeautifulIntegers(int low, int high, int kk)
    {
        string num = to_string(high);
        int a, b = 0; 
        a = dfs(num, "", kk, 0, true, 0, 0);
        if (low)
        {
            string num = to_string(low - 1);
            b = dfs(num, "", kk, 0, true, 0, 0);
        }
        return a - b;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << sol.numberOfBeautifulIntegers(1, 1100, 11) << endl;
    cout << sol.numberOfBeautifulIntegers(1, 20, 20) << endl;
    // cout << sol.numberOfBeautifulIntegers(5, 5, 2) << endl;
    // cout << sol.numberOfBeautifulIntegers(1, 10, 1) << endl;
    // cout << sol.numberOfBeautifulIntegers(10, 20, 3) << endl;

    // for (int i = 20; i >= 0; --i)
    //     cout << sol.numberOfBeautifulIntegers(0, i, i) << endl;
}