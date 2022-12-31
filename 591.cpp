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
    bool isTagValid(const string &s)
    {
        if (s.size() > 9)
            return false;
        for (auto &c : s)
            if (!isupper(c))
                return false;
        return true;
    }

public:
    bool isValid(string code)
    {
        int n = code.size();
        string token;
        vector<string> tags;
        int content = 0;
        int tags_count = 0;
        for (auto i = 0; i < n; ++i)
        {
            if (code[i] == '<')
            {
                token += code[i++];

                // start tag
                if (isupper(code[i]))
                {
                    while (i < n && code[i] != '>')
                        token += code[i++];
                    token += code[i];
                    if (!isTagValid(token.substr(1, token.size() - 2)))
                        return false;
                    if (tags.size())
                        ++content;
                    tags.push_back(token);
                    token.clear();
                    ++tags_count;
                }
                // end tag
                else if (code[i] == '/')
                {
                    // if (content == 0)
                    //     return false;
                    while (i < n && code[i] != '>')
                        token += code[i++];
                    token += code[i];
                    if (!isTagValid(token.substr(2, token.size() - 3)))
                        return false;
                    if (tags.empty())
                        return false;
                    if (tags.back().substr(1, tags.back().size() - 2) != token.substr(2, token.size() - 3))
                        return false;
                    tags.pop_back();
                    token.clear();
                }
                else if (code[i] == '!')
                {
                    ++content;
                    if (tags.empty())
                        return false;
                    while (i < n)
                    {
                        token += code[i++];
                        if (token.size() >= 3 && token.substr(token.size() - 3) == "]]>")
                            break;
                    }
                    if (token.substr(0, 9) != "<![CDATA[")
                        return false;
                    if (token.substr(token.size() - 3) != "]]>")
                        return false;
                    token.clear();
                    --i;
                }
            }
            else
                ++content;
        }

        if (tags_count == 0)
            return false;

        if (tags.size())
            return false;

        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isValid("<A><A>/A></A></A>");
    cout << r << endl;

    r = sol.isValid("<A>  <B> </A>   </B>");
    cout << r << endl;

    r = sol.isValid("<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>");
    cout << r << endl;

    r = sol.isValid("<DIV>This is the first line <![CDATA[<div>]]></DIV>");
    cout << r << endl;
}