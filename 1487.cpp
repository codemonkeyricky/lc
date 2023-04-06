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
    vector<string> getFolderNames(vector<string> &names)
    {
        unordered_map<string, int> seen; // A map to store whether the particular name occurs how many times already
        for (int i = 0; i < names.size(); i++)
        {
            if (seen.count(names[i])) // if the name already came
            {
                int k = seen[names[i]]; // it contains the number in brackets
                // Increase number until that didn't exist
                // mean while update in the map too
                while (seen.count(names[i] + "(" + to_string(k) + ")"))
                    ++k, ++seen[names[i]];
                ++seen[names[i]]; // Recently we will use one more number so increment
                names[i] = names[i] + "(" + to_string(k) + ")";
            }
            seen[names[i]] = 1; // Here we are storing  for example ...abc(1)=1 and abc(2)=1 it means abc(1) occcured one time, and abc=2 it means abc occured 2 times.
                             /*
                             Suppose you have a file named ABC occurring twice, we will store ABC with occurrence =2 and ABC(1) with occurrence =1... It helps when we get another file with name ABC(1) we can store like ABC(1)(1)
                             */
        }
        return names;
    }
};

int main()
{
    Solution sol;
    vector<string> r;

    r = sol.getFolderNames(vector<string>() = {"onepiece", "onepiece(1)", "onepiece(2)", "onepiece(3)", "onepiece"});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.getFolderNames(vector<string>() = {"gta", "gta(1)", "gta", "avalon"});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.getFolderNames(vector<string>() = {"pes", "fifa", "gta", "pes(2019)"});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}