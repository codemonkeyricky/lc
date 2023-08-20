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
    int longestValidSubstring(string word, vector<string> &forbidden)
    {
        unordered_set<string> set(forbidden.begin(), forbidden.end());
        int rv = 0, n = word.size(); 
        int j = 0, i = -1;
        string curr;
        while (j < n)
        {
            curr += word[j];
            string su;
            for (int k = j; k > (j - 10) && k > i; --k)
            {
                su = word[k] + su;
                if (set.count(su))
                {
                    curr = "";
                    i = k;
                    for (auto kk = k + 1; kk <= min(j, n - 1); ++kk)
                        curr += word[kk];
                    break;
                }
            }
            int l = curr.size();
            rv = max(rv, l);
            ++j;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.longestValidSubstring("bbc", vector<string>() = {"baba", "babc", "bbc", "bbc"});
    // cout << r << endl;

    // r = sol.longestValidSubstring("a", vector<string>() = {"n"});
    // cout << r << endl;

    // r = sol.longestValidSubstring("leetcode", vector<string>() = {"de", "le", "e"});
    // cout << r << endl;

    r = sol.longestValidSubstring("cbaaaabc", vector<string>() = {"aaa", "cb"});
    cout << r << endl;
}