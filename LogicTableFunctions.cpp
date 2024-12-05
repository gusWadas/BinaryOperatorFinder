#include <iostream>
#include <vector>
#include <random>
#include <bitset>

#include "evol.h"

// Generate a random logic table
std::vector<bool> generate_random_logic_table(int input_size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    // Total table size is 2^input_size
    std::vector<bool> logic_table(1 << input_size);
    
    for (size_t i = 0; i < logic_table.size(); ++i) {
        logic_table[i] = dis(gen);
    }
    
    return logic_table;
}

// Evaluate logic table for a given binary input
int evaluate_logic_table(const std::vector<bool>& logic_table, const std::vector<int>& input) {
    // Convert binary input to table index
    int index = 0;
    for (int bit : input) {
        index = (index << 1) | bit;
    }
    
    return logic_table[index];
}

int main() {
    // Example usage
    auto logic_table = generate_random_logic_table(N_BITS);
    
    // Create a sample binary input
    std::vector<int> input(N_BITS, 0);
    input[N_BITS-1] = 1;  // Set last bit to demonstrate
    
    int result = evaluate_logic_table(logic_table, input);
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}