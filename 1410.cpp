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
    string entityParser(string text)
    {
        string rv, token;
        for (auto &c : text)
            if (token.empty())
            {
                // non-token
                if (c == '&')
                    token += c; // switch to token mode
                else
                    rv += c;
            }
            else 
            {
                // token mode
                if (c == ';')
                {
                    token += c;
                    if (token == "&quot;")
                        token.clear(), rv += "\"";
                    else if (token == "&apos;")
                        token.clear(), rv += "'";
                    else if (token == "&amp;")
                        token.clear(), rv += "&";
                    else if (token == "&gt;")
                        token.clear(), rv += ">";
                    else if (token == "&lt;")
                        token.clear(), rv += "<";
                    else if (token == "&frasl;")
                        token.clear(), rv += "/";
                }
                else if (c == '&')
                {
                    rv += token; 
                    token.clear();
                    token += c;
                }
                else
                    token += c;
            }
        rv += token;
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.entityParser("&amp; is an HTML entity but &ambassador; is not.");
    cout << r << endl;
}