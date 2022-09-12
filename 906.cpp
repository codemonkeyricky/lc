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
    bool isPalindrome(long long n) 
    {
        auto s = to_string(n);
        int i = 0, j = s.size() - 1;
        while (i < j)
            if (s[i++] != s[j--])
                return false;
        return true;
    }

public:
    int superpalindromesInRange(string left, string right)
    {
        auto left_int = stoll(left);
        auto right_int = stoll(right);
        unordered_set<int> uniq;
        int mmax = sqrt(stoll("999999999999999999"));
        for (auto i = 1;; ++i)
        {
            auto s = to_string(i);
            auto l = s; 
            auto r = l; 
            reverse(begin(r), end(r));

            long long c = stoll(l + r);
            if (c <= mmax && isPalindrome(c * c))
                if (left_int <= c * c && c * c <= right_int)
                    uniq.insert(c);

            auto m = l.back();
            l.pop_back(); 
            r = l;
            reverse(begin(r), end(r));

            c = stoll(l + m + r);
            if (c <= mmax && isPalindrome(c * c))
                if (left_int <= c * c && c * c <= right_int)
                    uniq.insert(c);

            if (c > mmax || c * c > right_int)
                break;
        }
        return uniq.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.superpalindromesInRange("38455498359", "999999999999999999");
    cout << r << endl;

    r = sol.superpalindromesInRange("1", "100000000000000000");
    cout << r << endl;

    r = sol.superpalindromesInRange("1", "1000000000000");
    cout << r << endl;

    r = sol.superpalindromesInRange("1", "2");
    cout << r << endl;

    r = sol.superpalindromesInRange("4", "1000");
    cout << r << endl;
}