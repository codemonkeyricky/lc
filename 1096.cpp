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
    set<string> mul(set<string> &a, set<string> &b)
    {
        if (a.empty() || b.empty())
            return a.empty() ? b : a;
        set<string> rv;
        for (auto &aa : a)
            for (auto &bb : b)
                rv.insert(aa + bb);
        return rv;
    }

public:
    vector<string> braceExpansionII(string s)
    {
        vector<set<string>> stack;
        set<string> prev, curr;

        for (int i = 0; i < s.length(); ++i)
        {
            char c = s[i];
            if (c >= 'a' && c <= 'z')
            {
                if (curr.empty())
                    curr.insert(string(1, c));
                else
                {
                    set<string> cross;
                    for (auto &s : curr)
                        cross.insert(s + c);
                    swap(curr, cross);
                }
            }
            else if (c == '{')
            {
                stack.push_back(prev);
                stack.push_back(curr);
                prev.clear();
                curr.clear();
            }
            else if (c == '}')
            {
                auto prevSet2 = stack.back();
                stack.pop_back();
                auto prevSet1 = stack.back();
                stack.pop_back();

                prev.insert(begin(curr), end(curr));
                curr = mul(prevSet2, prev);
                
                prev = prevSet1;
            }
            else if (c == ',')
            {
                prev.insert(begin(curr), end(curr));
                curr.clear();
            }
        }
        prev.insert(begin(curr), end(curr));
        return vector<string>(begin(prev), end(prev));
    }
};

int main()
{
    Solution sol;
    vector<string> rv;

    rv = sol.braceExpansionII("{{a,z},a{b,c},{ab,z}}");
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;

    rv = sol.braceExpansionII("{a,b}{c,{d,e}}");
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;

    rv = sol.braceExpansionII("{a,b}c{d,e}f");
    for (auto &r : rv)
        cout << r << ", ";
    cout << endl;
}