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

// class Solution
// {
// public:
//     int getMaxRepetitions(string s1, int n1, string s2, int n2)
//     {
//         string ss1;
//         unordered_set<int> set(begin(s2), end(s2));
//         for (auto &c : s1)
//             if (set.count(c))
//                 ss1 += c;
//         swap(s1, ss1);

//         if (s1.empty())
//             return 0;

//         int i, j;
//         for (i = 0, j = 0; i < s1.size() * n1; ++i)
//         {
//             if (i && j && i % s1.size() == 0 && j % s2.size() == 0)
//                 break;
//             if (s1[i % s1.size()] == s2[j % s2.size()])
//                 ++j;
//         }

//         auto nn1 = i / s1.size();
//         auto nn2 = j / s2.size();
//         int rv = n1 / nn1 * nn2 / n2;

//         if (n1 % nn1)
//         {
//             for (i = n1 / nn1 * nn1 * s1.size(), j = (nn1 * nn2) % n2; i <= s1.size() * n1; ++i)
//             {
//                 if (j && (j % (s2.size() * n2)) == 0)
//                     ++rv, j = 0;
//                 if (i < s1.size() * n1 && s1[i % s1.size()] == s2[j % s2.size()])
//                     ++j;
//             }
//         }

//         return rv;
//     }
// };

// class Solution
// {
// public:
//     int getMaxRepetitions(string s1, int n1, string s2, int n2)
//     {
//         vector<int> repeatCount(n1 + 1, 0);
//         vector<int> nextIndex(n1 + 1, 0);
//         int j = 0, cnt = 0;
//         for (int k = 1; k <= n1; ++k)
//         {
//             for (int i = 0; i < s1.size(); ++i)
//             {
//                 if (s1[i] == s2[j])
//                 {
//                     ++j;
//                     if (j == s2.size())
//                     {
//                         j = 0;
//                         ++cnt;
//                     }
//                 }
//             }
//             repeatCount[k] = cnt;
//             nextIndex[k] = j;
//             for (int start = 0; start < k; ++start)
//             {
//                 if (nextIndex[start] == j)
//                 { // see if you have met this nextIndex before
//                     // if found, you can calculate the 3 parts
//                     int prefixCount = repeatCount[start]; // prefixCount is the start-th repeatCount
//                     // (repeatCount[k] - prefixCount) is the repeatCount of one occurrance of the pattern
//                     // There are (n1 - start) / (k - start) occurrances of the pattern
//                     // So (n1 - start) / (k - start) * (repeatCount[k] - prefixCount) is the repeatCount of the repetitive part
//                     int patternCount = (n1 - start) / (k - start) * (repeatCount[k] - prefixCount);
//                     // The suffix contains the incomplete repetitive remnant (if any)
//                     // Its length is (n1 - start) % (k - start)
//                     // So the suffix repeatCount should be repeatCount[start + (n1 - start) % (k - start)] - prefixCount
//                     int suffixCount = repeatCount[start + (n1 - start) % (k - start)] - prefixCount;
//                     return (prefixCount + patternCount + suffixCount) / n2;
//                 }
//             }
//         }
//         return repeatCount[n1] / n2;
//     }
// };


class Solution
{
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2)
    {
        if (n1 == 0)
            return 0;
        int indexr[s2.size() + 1] = {}; // index at start of each s1 block
        int countr[s2.size() + 1] = {}; // count of repititions till the present s1 block
        int index = 0, count = 0;
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < s1.size(); j++)
            {
                if (s1[j] == s2[index])
                    ++index;
                if (index == s2.size())
                {
                    index = 0;
                    ++count;
                }
            }
            countr[i] = count;
            indexr[i] = index;
            for (int k = 0; k < i; k++)
            {
                if (indexr[k] == index)
                {
                    int prev_count = countr[k];
                    int pattern_count = (countr[i] - countr[k]) * (n1 - 1 - k) / (i - k);
                    int remain_count = countr[k + (n1 - 1 - k) % (i - k)] - countr[k];
                    return (prev_count + pattern_count + remain_count) / n2;
                }
            }
        }
        return countr[n1 - 1] / n2;
    }
};

int main()
{
    Solution sol;
    int r;

    // r = sol.getMaxRepetitions("phqghumeay", 100, "lnl", 1);
    // cout << r << endl;

    r = sol.getMaxRepetitions("caahumeayllfdxfircvscxggbwkfnqduxwfnfozvsrtkjprepggxrpnrvystmwcysyycqpevikeffmznimkkasvwsrenazkycxaa", 1000000, "aac", 100);
    cout << r << endl;

    r = sol.getMaxRepetitions("aaaaaaaaaaaaaaaaa", 18, "aaaa", 9);
    cout << r << endl;

    r = sol.getMaxRepetitions("baba", 11, "baab", 1);
    cout << r << endl;

    r = sol.getMaxRepetitions("aaa", 3, "aa", 1);
    cout << r << endl;

    r = sol.getMaxRepetitions("acb", 1, "acb", 1);
    cout << r << endl;

    r = sol.getMaxRepetitions("abc", 4, "ab", 2);
    cout << r << endl;
}