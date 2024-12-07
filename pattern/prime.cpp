#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

#if 0

#include <array>
#include <iostream>

// Recursive template to check if a number is prime
template <size_t N, size_t D>
struct IsPrimeHelper {
    static constexpr bool value = (N % D != 0) && IsPrimeHelper<N, D - 1>::value;
};

// Base case: If D is 1, the number is prime

template <size_t N>
struct IsPrimeHelper<N, 0> {
    static constexpr bool value = true;
};

template <size_t N>
struct IsPrimeHelper<N, 1> {
    static constexpr bool value = true;
};

// Specialization for numbers less than 2 (not prime)
template <size_t N>
struct IsPrime {
    static constexpr bool value = IsPrimeHelper<N, N / 2>::value;
};

template <std::size_t M, std::size_t I = 0>
struct is_prime_array {
    static constexpr std::array<bool, M + 1> generate() {
        std::array<bool, M + 1> primes = {};
        if constexpr (I <= M) {
            primes[I] = IsPrime<I>::value;
            constexpr auto next_primes = is_prime_array<M, I + 1>::generate();
            for (std::size_t j = 0; j <= M; ++j) {
                primes[j] = primes[j] || next_primes[j];
            }
        }
        return primes;
    }
    static constexpr auto value = generate();
};

int main() {
    volatile auto primes_up_to_10 = is_prime_array<1000>::value;
}

#endif

// All done during compile time
// -------------------------------------------------------------------

// Function to determine if a number is prime at compile time
constexpr bool isPrime(size_t n) noexcept {
    if (n <= 1)
        return false;
    for (size_t i = 2; i * i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Helper to generate a constexpr std::array with a generator function
template <typename Generator, size_t... Indices>
constexpr auto is_prime_helper(Generator generator,
                               std::index_sequence<Indices...>) {
    return std::array<decltype(generator(size_t{})), sizeof...(Indices)>{
        generator(Indices)...};
}

template <size_t Size, typename Generator>
constexpr auto generate_is_prime(Generator generator) {
    return is_prime_helper(generator, std::make_index_sequence<Size>());
}

// Generates a boolean array where array[i] = true if i is prime
template <size_t N> constexpr auto get_prime_table() {
    return generate_is_prime<N + 1>([](size_t i) { return isPrime(i); });
}

// Generate prime table for a given N

// End of: All done during compile time
// -----------------------------------------------------------

// Some debug test driver code
int main() {

    constexpr size_t N = 100000; // Change N here to desired value
    constexpr auto is_prime = get_prime_table<N>();

    for (size_t i = 0; i <= N; ++i) {
        if (is_prime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << '\n';
    return 0;
}
