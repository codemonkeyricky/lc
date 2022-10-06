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

struct Node {
    string name;
    map<string, Node*> next; // mapping from folder name to the corresponding child node.
    bool del = false; // whether this folder is deleted.
    Node(string n = "") : name(n) {}
};

class Solution
{
    void addPath(Node *node, vector<string> &path)
    { // Given a path, add nodes to the folder tree. This is similar to the Trie build process.
        for (auto &s : path)
        {
            if (node->next.count(s) == 0)
                node->next[s] = new Node(s);
            node = node->next[s];
        }
    }
    unordered_map<string, Node *> seen; // mapping from subfolder structure string to the first occurrence node.
    string dedupe(Node *node)
    { // post-order traversal to dedupe. If we've seen the subfolder structure before, mark it as deleted.
        string subfolder;
        for (auto &[name, next] : node->next)
        {
            subfolder += dedupe(next);
        }
        if (subfolder.size())
        { // leaf nodes should be ignored
            if (seen.count(subfolder))
            { // if we've seen this subfolder structure before, mark them as deleted.
                seen[subfolder]->del = node->del = true;
            }
            else
            {
                seen[subfolder] = node; // otherwise, add the mapping
            }
        }
        return "(" + node->name + subfolder + ")"; // return the folder structure string of this node.
    }
    vector<vector<string>> ans;
    vector<string> path;
    void getPath(Node *node)
    {
        if (node->del)
            return; // if the current node is deleted, skip it.
        path.push_back(node->name);
        ans.push_back(path);
        for (auto &[name, next] : node->next)
        {
            getPath(next);
        }
        path.pop_back();
    }

public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>> &A)
    {
        Node root;
        for (auto &path : A)
            addPath(&root, path);
        dedupe(&root);
        for (auto &[name, next] : root.next)
            getPath(next);
        return ans;
    }
};

int main()
{
    // {
    //     Solution sol;
    //     vector<vector<string>> rv;

    //     rv = sol.deleteDuplicateFolder(vector<vector<string>>() = {{"y"}, {"y", "b"}, {"y", "b", "a"}, {"y", "d"}, {"y", "d", "c"}, {"z"}, {"z", "d"}, {"z", "d", "c"}, {"z", "d", "c", "b"}, {"z", "d", "c", "b", "a"}});
    //     for (auto &r : rv)
    //     {
    //         for (auto &w : r)
    //             cout << w << ", ";
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // {
    //     Solution sol;
    //     vector<vector<string>> rv;

    //     rv = sol.deleteDuplicateFolder(vector<vector<string>>() = {{"a"}, {"a", "c"}, {"a", "d"}, {"a", "d", "e"}, {"b"}, {"b", "e"}, {"b", "c"}, {"b", "c", "d"}, {"f"}, {"f", "h"}, {"f", "h", "i"}, {"f", "j"}, {"g"}, {"g", "j"}, {"g", "h"}, {"g", "h", "i"}});
    //     for (auto &r : rv)
    //     {
    //         for (auto &w : r)
    //             cout << w << ", ";
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    {
        Solution sol;
        vector<vector<string>> rv;

        rv = sol.deleteDuplicateFolder(vector<vector<string>>() = {{"a"}, {"c"}, {"a", "b"}, {"c", "b"}, {"a", "b", "x"}, {"a", "b", "x", "y"}, {"w"}, {"w", "y"}});
        for (auto &r : rv)
        {
            for (auto &w : r)
                cout << w << ", ";
            cout << endl;
        }
        cout << endl;
    }
}