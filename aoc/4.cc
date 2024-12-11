
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dfs(vector<vector<char>>& g, int i, int j, array<int, 2> dir, int k) {
    int m = g.size(), n = g[0].size();

    if (k == 0 && g[i][j] != 'X') {
        return false;
    } else if (k == 1 && g[i][j] != 'M') {
        return false;
    } else if (k == 2 && g[i][j] != 'A') {
        return false;
    } else if (k == 3) {
        return g[i][j] == 'S';
    }

    vector<int> offset = {0, -1, 0, 1, 0};
    int rv = 0;
    auto ni = i + dir[0];
    auto nj = j + dir[1];
    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
        rv += dfs(g, ni, nj, dir, k + 1);
    }
    return rv;
}

int main() {
    std::ifstream inputFile("4.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file 'input.txt'." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> g;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(),
                              line.end()); // Convert string to vector<char>
        g.push_back(row);                  // Add the row to the 2D vector
    }

    inputFile.close();

    int m = g.size(), n = g[0].size();
    int rv = 0;
#if 0
    for (auto i = 0; i < g.size(); ++i) {
        for (auto j = 0; j < g[0].size(); ++j) {
            for (auto k = -1; k <= 1; ++k) {
                for (auto l = -1; l <= 1; ++l) {
                    if (!(k == 0 && l == 0)) {
                        rv += dfs(g, i, j, {k, l}, 0);
                    }
                }
            }
        }
    }
#else
    for (auto i = 1; i < m - 1; ++i) {
        for (auto j = 1; j < n - 1; ++j) {
            if (g[i][j] == 'A') {
                auto tl = g[i - 1][j - 1];
                auto tr = g[i - 1][j + 1];
                auto bl = g[i + 1][j - 1];
                auto br = g[i + 1][j + 1];
                auto top_s = (tl == tr) && (tl == 'S');
                auto top_m = (tl == tr) && (tl == 'M');
                auto bot_s = (bl == br) && (bl == 'S');
                auto bot_m = (bl == br) && (bl == 'M');
                auto left_s = (bl == tl) && (bl == 'S');
                auto left_m = (bl == tl) && (bl == 'M');
                auto right_s = (tr == br) && (tr == 'S');
                auto right_m = (tr == br) && (tr == 'M');

                rv += top_s && bot_m;
                rv += top_m && bot_s;
                rv += left_s && right_m;
                rv += left_m && right_s;
            }
        }
    }
#endif

    cout << rv << endl;

    return 0;
}
