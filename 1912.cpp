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
#include <functional>

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

vector<array<int, 3>> lookup; ///< id -> shop/movie/price
struct comp
{
    bool operator()(int l, int r) const
    {
        if (lookup[l][2] == lookup[r][2])
            if (lookup[l][0] == lookup[r][0])
                return lookup[l][1] < lookup[r][1];
            else
                return lookup[l][0] < lookup[r][0];
        return lookup[l][2] < lookup[r][2];
    }
};
class MovieRentingSystem
{
    unordered_map<int, set<int, comp>> movies; ///< movie -> shop
    unordered_map<int, set<int, comp>> shops;  ///< shop -> movie
    set<int, comp> rented;                     ///< id
    map<array<int, 2>, int> rlookup;           ///< shop/movie -> id

public:
    MovieRentingSystem(int n, vector<vector<int>> &entries)
    {
        auto id = 0;
        for (auto &e : entries)
        {
            int s = e[0], m = e[1], p = e[2];
            auto id = lookup.size();
            lookup.push_back({s, m, p});
            rlookup[{s, m}] = id;
            movies[m].insert(id);
            shops[s].insert(id);
        }
    }

    vector<int> search(int movie)
    {
        vector<int> rv;
        auto it = begin(movies[movie]);
        for (int i = 0; it != end(movies[movie]) && i < 5; ++i, ++it)
            rv.push_back(lookup[*it][0]);
        return rv;
    }

    void rent(int shop, int movie)
    {
        auto id = rlookup[{shop, movie}];
        rented.insert(id);
        movies[movie].erase(id);
        shops[shop].erase(id);
    }

    void drop(int shop, int movie)
    {
        auto id = rlookup[{shop, movie}];
        rented.erase(id);
        movies[movie].insert(id);
        shops[shop].insert(id);
    }

    vector<vector<int>> report()
    {
        vector<vector<int>> rv;
        auto it = begin(rented);
        for (int i = 0; it != end(rented) && i < 5; ++i, ++it)
            rv.push_back({lookup[*it][0], lookup[*it][1]});
        return rv;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */

int main()
{

    {
        MovieRentingSystem mrs(1, vector<vector<int>>() = {{0, 1, 3}, {0, 5, 3}, {0, 7, 3}, {0, 6, 3}, {0, 2, 3}, {0, 3, 3}, {0, 4, 3}, {0, 8, 3}});
        mrs.rent(0, 1);
        mrs.rent(0, 4);
        mrs.report(); 
    }

    MovieRentingSystem mrs(3, vector<vector<int>>() = {{0, 1, 5}, {0, 2, 6}, {0, 3, 6}, {1, 1, 4}, {1, 2, 7}, {2, 1, 5}});
    auto r = mrs.search(1);
    cout << endl;
}