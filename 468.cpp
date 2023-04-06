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
    bool isIpv4(string &ip)
    {
        string chunk;
        for (auto i = 0; i <= ip.size(); ++i)
            if (i == ip.size() || ip[i] == '.')
            {
                if (chunk.empty() || (chunk.size() > 1 && chunk[0] == '0') || chunk.size() > 3 || stoi(chunk) < 0 || stoi(chunk) > 255)
                    return false;
                chunk.clear();
            }
            else if (!isdigit(ip[i]))
                return false;
            else 
                chunk += ip[i];
        return true;
    }

    bool isIpv6(string &ip)
    {
        string chunk;
        for (auto i = 0; i <= ip.size(); ++i)
            if (i == ip.size() || ip[i] == ':')
            {
                if (chunk.size() < 1 || chunk.size() > 4)
                    return false;
                chunk.clear();
            }
            else if (!isalnum(ip[i]))
                return false;
            else
            {
                ip[i] = tolower(ip[i]);
                if (isalpha(ip[i]))
                    if (!('a' <= ip[i] && ip[i] <= 'f'))
                        return false;
                chunk += ip[i];
            }
        return true;
    }

public:
    string validIPAddress(string ip)
    {
        auto dots = count_if(begin(ip), end(ip), [](char c)
                             { return c == '.'; });
        if (dots == 3)
            return isIpv4(ip) ? "IPv4" : "Neither";
        else 
        {
            auto cols = count_if(begin(ip), end(ip), [](char c)
                                 { return c == ':'; });

            if (cols != 7)
                return "Neither";

            return isIpv6(ip) ? "IPv6" : "Neither";
        }
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.validIPAddress("192.0.0.1");
    cout << r << endl;

    r = sol.validIPAddress("256.256.256.256");
    cout << r << endl;

    r = sol.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334");
    cout << r << endl;

    r = sol.validIPAddress("172.16.254.1");
    cout << r << endl;
}