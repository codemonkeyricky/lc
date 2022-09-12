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
#include <climits>

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
    int n, cand, bn, minlen, minab;
    vector<int> dict;

    // Return the length of abbreviation given bit sequence
    int abbrLen(int mask)
    {
        int count = 0;
        for (int b = 1; b < bn;)
        {
            if ((mask & b) == 0)
                for (; b < bn and (mask & b) == 0; b <<= 1)
                    ;
            else
                b <<= 1;
            count++;
        }
        return count;
    }

    // DFS backtracking
    void dfs(int bit, int mask)
    {
        int len = abbrLen(mask);
        if (len >= minlen)
            return;
        bool match = true;
        for (auto d : dict)
        {
            if ((mask & d) == 0)
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            minlen = len;
            minab = mask;
        }
        else
            for (int b = bit; b < bn; b <<= 1)
                if (cand & b)
                    dfs(b << 1, mask + b);
    }

public:
    string minAbbreviation(string target, vector<string> &dictionary)
    {
        n = target.size(), bn = 1 << n, cand = 0, minlen = INT_MAX;

        // Preprocessing with bit manipulation
        for (auto w : dictionary)
        {
            int word = 0;
            if (w.size() == n)
            {
                for (int i = n - 1, bit = 1; i >= 0; --i, bit <<= 1)
                    if (target[i] != w[i])
                        word += bit;
                dict.push_back(word);
                cand |= word;
            }
        }
        dfs(1, 0);

        // Reconstruct abbreviation from bit sequence
        string rv;
        for (int i = n - 1, pre = i; i >= 0; --i, minab >>= 1)
        {
            if (minab & 1)
            {
                if (pre - i > 0)
                    rv = to_string(pre - i) + rv;
                pre = i - 1;
                rv = target[i] + rv;
            }
            else if (i == 0)
                rv = to_string(pre - i + 1) + rv;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.minAbbreviation("aabadaa", vector<string>() = {"aabaxaa","aaxadaa"});
    cout << r << endl;

    r = sol.minAbbreviation("usaandchinaarefriends", vector<string>() = {});
    cout << r << endl;

    r = sol.minAbbreviation("abcdef", vector<string>() = {"abcde"});
    cout << r << endl;

    r = sol.minAbbreviation("abcdef", vector<string>() = {"ablade", "xxxxef", "abdefi"});
    cout << r << endl;

    r = sol.minAbbreviation("apple", vector<string>() = {"blade", "plain", "amber"});
    cout << r << endl;

    r = sol.minAbbreviation("apple", vector<string>() = {"blade"});
    cout << r << endl;
}