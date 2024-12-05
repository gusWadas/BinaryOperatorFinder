#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "evol.h"

const int T_TABLES = N_BITS * 10;

std::vector<bool> generate_random_logic_table(int input_size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    std::vector<bool> logic_table(1 << input_size);
    for (size_t i = 0; i < logic_table.size(); ++i) {
        logic_table[i] = dis(gen);
    }
    
    return logic_table;
}

int evaluate_logic_table(const std::vector<bool>& logic_table, const std::vector<int>& input) {
    int index = 0;
    for (int bit : input) {
        index = (index << 1) | bit;
    }
    
    return logic_table[index];
}

std::pair<std::vector<int>, std::vector<int>> generate_random_sqrt_binary() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, (1 << N_BITS) - 1);
    
    int original_number = dis(gen);
    int sqrt_number = static_cast<int>(std::floor(std::sqrt(original_number)));
    sqrt_number = std::min(sqrt_number, (1 << N_BITS) - 1);
    
    std::vector<int> original_binary(N_BITS, 0);
    std::vector<int> sqrt_binary(N_BITS, 0);
    
    for (int i = 0; i < N_BITS; ++i) {
        original_binary[N_BITS - 1 - i] = (original_number >> i) & 1;
        sqrt_binary[N_BITS - 1 - i] = (sqrt_number >> i) & 1;
    }
    
    return {original_binary, sqrt_binary};
}

int main() {
    std::vector<std::vector<bool>> tables(T_TABLES);
    for (auto& table : tables) {
        table = generate_random_logic_table(N_BITS);
    }
    
    std::vector<std::vector<std::pair<int, int>>> scores(
        T_TABLES, std::vector<std::pair<int, int>>(N_BITS, {0, 0})
    );
    
    for (int test = 0; test < (N_BITS/2)*5; ++test) {
        auto [original_binary, sqrt_binary] = generate_random_sqrt_binary();
        
        for (int table_idx = 0; table_idx < T_TABLES; ++table_idx) {
            int table_result = evaluate_logic_table(tables[table_idx], original_binary);
            
            for (int bit_idx = 0; bit_idx < N_BITS; ++bit_idx) {
                scores[table_idx][bit_idx].second++;
                
                if (table_result == sqrt_binary[bit_idx]) {
                    scores[table_idx][bit_idx].first++;
                }
            }
        }
    }
    
    return 0;
}