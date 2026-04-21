#include <iostream>
#include <vector>

using namespace std;

int main() {
    int D;
    long long n_orig;
    if (!(cin >> D >> n_orig)) return 0;

    // Part 1: Position of the n-th ball
    long long n = n_orig;
    int k = 1;
    for (int i = 0; i < D - 1; ++i) {
        if (n % 2 == 1) { // Odd-th ball at this node goes left
            k = 2 * k;
            n = (n + 1) / 2;
        } else { // Even-th ball at this node goes right
            k = 2 * k + 1;
            n = n / 2;
        }
    }
    cout << k << endl;

    // Part 2: Switch states of leaf nodes
    // Each node k gets some number of balls.
    // If it gets B balls, B % 2 is its final state (1 if odd, 0 if even).
    // Root (node 1) gets n_orig balls.
    // Node k at depth d (d < D) gets B balls:
    // Left child (2k) gets (B+1)/2 balls.
    // Right child (2k+1) gets B/2 balls.

    // We only need the states of leaves (depth D).
    // The number of nodes is 2^D - 1.
    // D <= 20, so 2^20 - 1 is about 1 million.
    // We can use an array to store the number of balls at each node.

    int total_nodes = (1 << D);
    vector<long long> balls(total_nodes, 0);
    balls[1] = n_orig;

    for (int i = 1; i < (1 << (D - 1)); ++i) {
        long long B = balls[i];
        balls[2 * i] = (B + 1) / 2;
        balls[2 * i + 1] = B / 2;
    }

    int first_leaf = 1 << (D - 1);
    for (int i = 0; i < (1 << (D - 1)); ++i) {
        cout << (balls[first_leaf + i] % 2) << (i == (1 << (D - 1)) - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
