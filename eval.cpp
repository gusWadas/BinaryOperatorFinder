#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

#include "evol.h"
#include "LogicTableFunctions.h"
#include "reproduction.h"
#include "epoch.h"


// Previous functions (generate_random_logic_table, evaluate_logic_table, generate_random_sqrt_binary)
// are the same as in the previous implementation

// Mutation and combination functions from previous implementations
std::vector<bool> mutate_table_10_percent(std::vector<bool> original_table) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for (size_t i = 0; i < original_table.size(); ++i) {
        if (dis(gen) < 0.1) {
            original_table[i] = 1 - original_table[i];
        }
    }
    
    return original_table;
}

std::vector<bool> combine_tables_half(const std::vector<bool>& table1, const std::vector<bool>& table2) {
    std::vector<bool> combined_table(table1.size());
    size_t half_size = table1.size() / 2;
    
    std::copy(table1.begin(), table1.begin() + half_size, combined_table.begin());
    std::copy(table2.begin() + half_size, table2.end(), combined_table.begin() + half_size);
    
    return combined_table;
}

std::vector<bool> combine_tables_three_quarters(const std::vector<bool>& table1, const std::vector<bool>& table2) {
    std::vector<bool> combined_table(table1.size());
    size_t three_quarters_size = table1.size() * 3 / 4;
    
    std::copy(table1.begin(), table1.begin() + three_quarters_size, combined_table.begin());
    std::copy(table2.begin() + three_quarters_size, table2.end(), combined_table.begin() + three_quarters_size);
    
    return combined_table;
}

int main() {
    // Initial setup (same as previous implementation)
    std::vector<std::vector<bool>> tables(T_TABLES);
    for (auto& table : tables) {
        table = generate_random_logic_table(N_BITS);
    }
    
    std::vector<std::vector<std::pair<int, int>>> scores(
        T_TABLES, std::vector<std::pair<int, int>>(N_BITS, {0, 0})
    );
    
    // Testing phase (same as previous implementation)
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
    
    // Find top 5 tables for each bit column
    std::vector<std::vector<int>> top_tables_per_bit(N_BITS);
    for (int bit_idx = 0; bit_idx < N_BITS; ++bit_idx) {
        std::vector<std::pair<int, int>> bit_column_scores;
        for (int table_idx = 0; table_idx < T_TABLES; ++table_idx) {
            bit_column_scores.push_back({scores[table_idx][bit_idx].first, table_idx});
        }
        
        std::sort(bit_column_scores.rbegin(), bit_column_scores.rend());
        
        for (int i = 0; i < 5; ++i) {
            top_tables_per_bit[bit_idx].push_back(bit_column_scores[i].second);
        }
    }
    
    // Eliminate and replace tables
    std::vector<std::vector<bool>> new_tables;
    for (int bit_idx = 0; bit_idx < N_BITS; ++bit_idx) {
        // Keep top tables
        for (int top_idx : top_tables_per_bit[bit_idx]) {
            new_tables.push_back(tables[top_idx]);
        }
        
        // Combine top tables half and half
        new_tables.push_back(combine_tables_half(
            tables[top_tables_per_bit[bit_idx][0]], 
            tables[top_tables_per_bit[bit_idx][1]]
        ));
        
        // Combine 3/4 top and 1/4 non-top table
        new_tables.push_back(combine_tables_three_quarters(
            tables[top_tables_per_bit[bit_idx][0]], 
            tables[top_tables_per_bit[bit_idx][5]]
        ));
        
        // Combine top tables with mutation
        auto combined = combine_tables_half(
            tables[top_tables_per_bit[bit_idx][0]], 
            tables[top_tables_per_bit[bit_idx][1]]
        );
        new_tables.push_back(mutate_table_10_percent(combined));
        
        // Mutate top tables
        for (int top_idx : top_tables_per_bit[bit_idx]) {
            new_tables.push_back(mutate_table_10_percent(tables[top_idx]));
        }
    }
    
    // Update tables
    tables = new_tables;
    
    return 0;
}