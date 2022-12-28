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
    int lengthLongestPath(string input)
    {
        vector<string> path;
        int i = 0, n = input.size(), len = 0;
        int rv = 0;
        while (i < n)
        {
            int depth = 0;
            while (i < n && input[i] == '\t')
                ++depth, ++i;
            string inode; 
            bool is_file = false;
            while (i < n && input[i] != '\n')
                inode += input[i], is_file |= input[i++] == '.';
            ++i;

            while (path.size() > depth)
                len -= path.back().size(), path.pop_back();

            path.push_back(inode);
            if (!is_file)
                path.back() += "/";
            len += path.back().size();

            if (path.back().back() != '/')
                rv = max(rv, len);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.lengthLongestPath("a\n\tb1\n\t\tf1.txt\n\taaaaa\n\t\tf2.txt");
    cout << r << endl;

    r = sol.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
    cout << r << endl;
}