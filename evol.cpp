#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <bitset>
#include <iomanip>

const int N_BITS = 8;

std::pair<std::vector<int>, std::vector<int>> generate_random_sqrt_binary() {
    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, (1 << N_BITS) - 1);
    
    // Generate random number
    int original_number = dis(gen);
    
    std::cout << original_number;
    std::cout << std::endl;
    // Calculate square root and round down
    int sqrt_number = static_cast<int>(std::floor(std::sqrt(original_number)));
    sqrt_number = std::min(sqrt_number, (1 << N_BITS) - 1);

    std::cout << sqrt_number;
    std::cout << std::endl;
    
    // Convert to binary digit vectors
    std::vector<int> original_binary(N_BITS, 0);
    std::vector<int> sqrt_binary(N_BITS, 0);
    
    for (int i = 0; i < N_BITS; ++i) {
        original_binary[N_BITS - 1 - i] = (original_number >> i) & 1;
        sqrt_binary[N_BITS - 1 - i] = (sqrt_number >> i) & 1;
    }
    
    return {original_binary, sqrt_binary};
}

int main() {
    auto [original, sqrt] = generate_random_sqrt_binary();
    
    // Print original number binary
    std::cout << "Original Number (Binary): ";
    for (int bit : original) std::cout << bit;
    std::cout << std::endl;
    
    // Print square root binary
    std::cout << "Square Root (Binary):     ";
    for (int bit : sqrt) std::cout << bit;
    std::cout << std::endl;
    
    return 0;
}