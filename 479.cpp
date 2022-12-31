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
    int largestPalindrome(int n)
    {
        long max = (long)pow(10, n) - 1;
        long min = max / 10;
        for (long h = max; h > min; h--)
        {
            long left = h, right = 0;
            for (long i = h; i != 0; right = right * 10 + i % 10, i /= 10, left *= 10)
                ;
            long palindrome = left + right; // construct the palindrome

            for (long i = max; i > min; i--)
            {
                long j = palindrome / i;
                if (j > i)
                    break; // terminate if the other number is greater than current number
                if (palindrome % i == 0)
                    return (int)(palindrome % 1337); // found if current number is a factor
            }
        }

        return 9; // account for case n = 1
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.largestPalindrome(8);
    cout << r << endl;
}