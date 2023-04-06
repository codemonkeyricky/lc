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
    int dp[4000] = {}, lps[4000] = {};
    int deleteString(string s)
    {
        for (int k = s.size() - 1; k >= 0; --k)
        {
            for (int j = 1, i = 0; j + k < s.size(); ++j)
            {
                while (i && s[j + k] != s[i + k])
                    i = max(0, lps[i] - 1);
                i += s[j + k] == s[i + k];
                lps[j] = i;
            }
            dp[k] = 1;
            for (int len = 1; k + 2 * len <= s.size(); ++len)
                if (lps[len * 2 - 1] == len)
                    dp[k] = max(dp[k], 1 + dp[k + len]);
        }
        return dp[0];
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.deleteString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    // cout << r << endl;

    // r = sol.deleteString("ilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkeilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkebqumabhsdwjesovwhqjvphhigtqubeazichenrkipozlnrjpmxojqmonwdwkeyfptfkwcwzyqglgrqoaiufbhcplnrhvljsjqvvcryxfiifzkvdwtrveehprjrycsiljusynfxtgvzhzczqhbmrfutryzguvpmsrsoudxbinfrdwadboontbjjbzbyhextdynmdwhodebxwgcdrvwtttvhuxzqweahbmfecmoawmwunzlltklrcchkvbpkbpfrupkwmbfmbmldefzichboxigbgusfyirfaypemrjqjaprtblyjdyyycqymoxuuwyvbyqeihlysakceywfjqczosimkpkiqyautfymxsgkiagshmdxgsudaijuxcrkbsrcedirltpjhrdozrghtvinqofwomywcharaabfprotzlmfhoxbzbamqypjwrlivyrytehwsmdxpdrlnxdiqagtfmuqvckqabvlmedptfaerixwsnzzzucildclmximjhpkcvvwadzwsquflhznwoeyhtiydbsivhimkynqydfkdjonicpywvtgtmwisetxsyjpuffvkhmdptagagrivjnsabgqoltdypvirauiwgjlupliioletrpthrslwyofyomldadbtqhoczvwczmfcfazncwrsvkotsognwpdcuounqhuhtstfaenrzwmhatnwqzdtqoscuxgxnsavyhplcgqczfamyyzyukfswpnjbyexesuhgmjhzfdrdmcjxcieiejwwenwnwbfxesanttgwarcykrclbzwmyj");
    // cout << r << endl;

    // r = sol.deleteString("dgehtytaaaaaaa");
    // cout << r << endl;

    // r = sol.deleteString("abaaa");
    // cout << r << endl;

    // r = sol.deleteString("aaabaab");
    // cout << r << endl;

    // r = sol.deleteString("aaaaa");
    // cout << r << endl;

    r = sol.deleteString("abcabcdabc");
    cout << r << endl;
}